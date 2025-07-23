# Importe as bibliotecas necessárias
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import torch
from torch.utils.data import DataLoader
from torch.optim.lr_scheduler import ReduceLROnPlateau
from pytorch_forecasting import TimeSeriesDataSet, TFT, TemporalFusionTransformer, QuantileLoss
from pytorch_forecasting.data import GroupNormalizer
from pytorch_forecasting.metrics import MAE
from pytorch_forecasting.data.encoders import EncoderNormalizer

# Gere dados fictícios de vendas
np.random.seed(42)
n_samples = 3 * 365  # 3 anos de dados
date_rng = pd.date_range(start="2020-01-01", periods=n_samples, freq="D")
sales = 100 + np.sin(np.linspace(0, 2 * np.pi, n_samples)) * 20 + np.random.randn(n_samples) * 5
df = pd.DataFrame({"date": date_rng, "sales": sales})

# Faça uma rápida exploração dos dados
print(df.head())

# Crie um TimeSeriesDataSet
max_prediction_length = 30  # Define o horizonte de previsão
max_encoder_length = 365  # Define o tamanho máximo do encoder
training_cutoff = df["date"].max() - pd.DateOffset(days=max_prediction_length)

data = TimeSeriesDataSet(
    df,
    time_idx="date",
    target="sales",
    group_ids=["date"],
    min_encoder_length=1,
    max_encoder_length=max_encoder_length,
    min_prediction_length=1,
    max_prediction_length=max_prediction_length,
    static_categoricals=[],
    static_reals=[],
    time_varying_categoricals=[],
    time_varying_reals=["sales"],
    target_normalizer=EncoderNormalizer(),
)

# Aplique o GroupNormalizer com transformation="softplus"
data.normalizer = GroupNormalizer(transform="softplus")

# Divida os dados em treino e teste
train_dataloader = DataLoader(data, batch_size=64, num_workers=4, shuffle=True)
val_dataloader = DataLoader(data, batch_size=64, num_workers=4, shuffle=False)

# Crie o modelo TFT
tft = TemporalFusionTransformer.from_dataset(data, learning_rate=0.03, hidden_size=8, loss=QuantileLoss(), optimizer="Ranger")

# Treine o modelo em GPU
tft, best_val = tft.fit(
    train_dataloader=train_dataloader,
    val_dataloaders=val_dataloader,
    epochs=100,
    early_stopping=EarlyStopping(monitor="val_loss", min_delta=1e-4, patience=10, verbose=False, mode="min"),
    reduce_on_plateau_callback=ReduceLROnPlateau(monitor="val_loss", patience=5, factor=0.5),
)

# Avalie a performance com a métrica MAE
metric = MAE()
result = tft.validate(val_dataloaders=val_dataloader, metrics=[metric])

# Crie um plot com a performance em treino
tft.plot_prediction(tft, df, plot_every_n_epochs=5, show_future_observed=True)

# Exiba a métrica MAE
print("MAE:", result[0]["MAE"])
