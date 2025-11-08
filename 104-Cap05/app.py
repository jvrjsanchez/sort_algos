# Projeto 2 - Web App com Inteligência Artificial Para Análise e Previsão de Preços de Ações

# Instale os pacotes via linha de comando:
# pip install -q -r requirements.txt

# Execute a app:
# streamlit run app.py

# Imports
import datetime
import pandas as pd
import streamlit as st
import yfinance as yf
from datetime import date
from ta.momentum import RSIIndicator
from ta.volatility import BollingerBands
from ta.trend import MACD, EMAIndicator, SMAIndicator
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score, mean_absolute_error

# Configuração da página do Streamlit
st.set_page_config(page_title = "Data Science Academy", page_icon = ":100:", layout = "centered")

# Título principal
st.title('Web App com Inteligência Artificial Para Análise e Previsão de Preços de Ações em Tempo Real')

# Adicionando o conteúdo da barra lateral
st.sidebar.header("Bem-Vindo(a)")
st.sidebar.info('Data Science Academy')
st.sidebar.info('Projeto 2')

# Adicionando um espaço em branco para ajustar o tamanho da barra lateral
st.sidebar.markdown("&#8203;" * 100)

# Módulo de seleção de página
def dsa_seleciona_pagina():

    # Cria um menu lateral com opções de seleção
    option = st.sidebar.selectbox('Selecione o Que Deseja Fazer', ['Visualizar Gráficos', 'Visualizar Tabela de Dados', 'Fazer Previsões'])
    
    # Verifica se a opção selecionada é 'Visualizar Gráficos' e chama a função correspondente
    if option == 'Visualizar Gráficos':
        dsa_indicadores_tecnicos()
        
    # Verifica se a opção selecionada é 'Visualizar Tabela de Dados' e chama a função correspondente
    elif option == 'Visualizar Tabela de Dados':
        dsa_imprime_tabela()
        
    # Se nenhuma das opções acima for selecionada, assume que a opção é 'Fazer Previsões' e chama a função correspondente
    else:
        dsa_previsoes()

# Módulo de download de dados de ativos financeiros
# Decorador que permite o cache de recursos no Streamlit para melhorar a performance da aplicação
@st.cache_resource
def dsa_download_dados(ticker, start_date, end_date):
    
    # Força strings “YYYY-MM-DD”
    start_str = start_date.isoformat()
    end_str   = end_date.isoformat()

    # Tenta obter pelo history()
    try:
        df = yf.Ticker(ticker).history(
            start = start_str,
            end = end_str,
            interval = "1d",        # diário
            auto_adjust = False,    # ou True, conforme você queira preço ajustado
            prepost = False         # sem pré/after-market
        )
    except Exception as e:
        st.error(f"Erro ao baixar dados de {ticker}: {e}")
        return pd.DataFrame()

    # avisa se realmente não veio nada
    if df.empty:
        st.error(f"Sem dados de preço para {ticker} de {start_str} até {end_str}.")
    return df

# Caixa de seleção lateral
option = st.sidebar.selectbox("Selecione a Empresa", ["Apple", "Google", "Microsoft", "Tesla", "Netflix", "Intel", "Taiwan", "Meta"])

# Converte a seleção para maiúsculo
option = option.upper()

# Imprime a opção
print(option)

# Caixa de seleção lateral para o número de pontos de dados (valor padrão de 3000, ou seja, aproximadamente 10 anos)
num_pontos_dados = st.sidebar.number_input('Número de Registros Para Treinar o Modelo', value = 3000)

# Registra a data atual
today = datetime.date.today()

# Obtém a data com a diferença entre a data atual e o número de pontos de dados selecionados
data_padrao = today - datetime.timedelta(days = num_pontos_dados)

# Input para data de início
start_date = st.sidebar.date_input('Selecione Uma Data Inicial', value = data_padrao)

# Input para data de fim
end_date = st.sidebar.date_input('Selecione Uma Data Final', today)

# Bloco condicional para obter o código da empresa selecionada, data de início e data de fim
if option=="APPLE":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "AAPL"
elif option=="GOOGLE":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "GOOG"
elif option=="MICROSOFT":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "MSFT"
elif option=="TESLA":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "TSLA"
elif option == "INTEL":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "INTC"
elif option == "TAIWAN":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "TSM"
elif option == "NETFLIX":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "NFLX"
elif option=="META":
    st.sidebar.success('Data Inicial da Coleta de Dados: `%s`\n\nData Final da Coleta de Dados: `%s`' %(start_date, end_date))
    stock = "META"

# Download dos dados
df_dsa_dados = dsa_download_dados(stock,start_date,end_date)

# Acompanhe as definições dos indicadores técnicos nos videobooks do Capítulo 5 do curso

# Define a função para exibir indicadores técnicos no Streamlit
def dsa_indicadores_tecnicos():
    
    # Cria um cabeçalho na página
    st.header('Indicadores Técnicos')
    
    # Cria um widget de seleção para escolher um indicador técnico
    option = st.radio('Selecione Um Indicador Técnico Para Visualizar', ['Preço de Fechamento', 
                                                                         'BollingerBands', 
                                                                         'Moving Average Convergence Divergence', 
                                                                         'Relative Strength Indicator', 
                                                                         'Simple Moving Average', 
                                                                         'Exponential Moving Average'])

    # Calcula as Bandas de Bollinger para o preço de fechamento
    indicador_bb = BollingerBands(df_dsa_dados.Close)
    
    # Prepara o DataFrame para os dados das Bandas de Bollinger
    df_bb = df_dsa_dados
    
    # Adiciona a banda superior de Bollinger ao DataFrame
    df_bb['bb_maximo'] = indicador_bb.bollinger_hband()
    
    # Adiciona a banda inferior de Bollinger ao DataFrame
    df_bb['bb_minimo'] = indicador_bb.bollinger_lband()
    
    # Seleciona apenas as colunas relevantes para exibição
    df_bb = df_bb[['Close', 'bb_maximo', 'bb_minimo']]
    
    # Calcula o objeto MACD para o preço de fechamento
    macd_object = MACD(df_dsa_dados['Close'])

    # Calcula o indicador RSI para o preço de fechamento
    rsi = RSIIndicator(df_dsa_dados.Close).rsi()
    
    # Calcula a Média Móvel Simples (SMA) para o preço de fechamento
    sma = SMAIndicator(df_dsa_dados.Close, window=14).sma_indicator()
    
    # Calcula a Média Móvel Exponencial (EMA) para o preço de fechamento
    ema = EMAIndicator(df_dsa_dados.Close).ema_indicator()

    # Condicional para verificar qual indicador foi escolhido e exibir os dados correspondentes
    if option == 'Preço de Fechamento':
        st.write('Preço de Fechamento')
        st.line_chart(df_dsa_dados.Close)
    
    elif option == 'BollingerBands':
        st.write('BollingerBands')
        st.line_chart(df_bb)
    
    elif option == 'Moving Average Convergence Divergence':
        st.write('Moving Average Convergence Divergence')

        # Se necessário, instale: pip install PyQt5
        import matplotlib.pyplot as plt

        # Extrai o MACD, o Sinal e a Diferença
        df_dsa_dados['MACD'] = macd_object.macd()
        df_dsa_dados['Signal_Line'] = macd_object.macd_signal()
        df_dsa_dados['MACD_Diff'] = macd_object.macd_diff()

        # Plot
        plt.figure(figsize=(14, 7))

        # Plot do Preço de Fechamento
        plt.subplot(2, 1, 1)
        plt.plot(df_dsa_dados['Close'], label='Close Price')
        plt.legend()

        # Plot do MACD
        plt.subplot(2, 1, 2)
        plt.plot(df_dsa_dados['MACD'], label='MACD', color='blue')
        plt.plot(df_dsa_dados['Signal_Line'], label='Sinal', color='magenta')
        plt.bar(df_dsa_dados.index, df_dsa_dados['MACD_Diff'], label='Histograma', color='black', alpha=0.8)
        plt.legend()
        st.pyplot(plt)
        
    elif option == 'Relative Strength Indicator':
        st.write('Relative Strength Indicator')
        st.line_chart(rsi)
    
    elif option == 'Simple Moving Average':
        st.write('Simple Moving Average')
        st.line_chart(sma)
    
    else:
        st.write('Exponential Moving Average')
        st.line_chart(ema)

# Função para mostrar os 20 últimos registros da tabela de dados
def dsa_imprime_tabela():
    st.header('Tabela de Dados')
    st.dataframe(df_dsa_dados.tail(20))

# Função para previsão
def dsa_previsoes():
    
    # Recebe o número de dias para a previsão
    num = st.number_input('Fazer a Previsão de Quantos Dias?', value = 1, min_value = 1)
    num = int(num)
    
    # Verifica se o botão 'Previsão' foi pressionado e se num é maior que 0
    if st.button('Previsão') and num > 0:
        dsa_inteligencia_artificial(num)
    elif num <= 0:
        st.error('Por favor, insira um número de dias maior que 0 para a previsão.')
      
# Módulo para fazer previsões a partir dos dados
def dsa_inteligencia_artificial(num):
    
    # Extrai o preço de fechamento
    df = df_dsa_dados[['Close']].copy() 

    # A nova coluna 'preds' conterá os valores da coluna 'Close' 
    # deslocados (shift) para cima por num posições.
    df['preds'] = df.Close.shift(-num)

    # Separa as variáveis de entrada e saída
    x = df.drop(['preds'], axis=1).values
    y = df.preds.values[:-num]
    
    # Divide os dados em treino e teste antes da padronização
    x_train, x_test, y_train, y_test = train_test_split(x[:-num], y, test_size = .2, random_state = 7)
    
    # Inicializa e ajusta o StandardScaler com os dados de treino
    scaler = StandardScaler()
    x_train_scaled = scaler.fit_transform(x_train)
    
    # Aplica a transformação aos dados de teste
    x_test_scaled = scaler.transform(x_test)
    
    # Treina o modelo com os dados de treino padronizados
    modelo_dsa = LinearRegression().fit(x_train_scaled, y_train)
    
    # Faz previsões com os dados de teste padronizados
    preds = modelo_dsa.predict(x_test_scaled)
    
    # Avalia a acurácia do modelo
    st.text(f'Previsão com Acurácia de: {r2_score(y_test, preds)}')
    
    # Prepara e faz previsões para os próximos 'num' dias
    # Nota: A padronização de 'x_forecast' deve ser feita com o mesmo scaler
    x_forecast = df.drop(['preds'], axis=1).values[-num:]
    x_forecast_scaled = scaler.transform(x_forecast)
    forecast_pred = modelo_dsa.predict(x_forecast_scaled)
    
    # Exibe as previsões para os próximos 'num' dias
    day = 1
    for i in forecast_pred:
        st.text(f'Previsão do Preço de Fechamento no Dia {day} é: {i}')
        day += 1

# Adiciona um rodapé simples ao final do aplicativo
st.caption('Data Science Academy. Projeto 2 do Curso Engenharia Financeira com IA.')

# Bloco principal do programa Python
if __name__ == '__main__':
        dsa_seleciona_pagina()
