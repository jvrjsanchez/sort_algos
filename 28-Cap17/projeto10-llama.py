# Projeto 10 - Robô Investidor com IA - Usando LLMs Para Investment Analytics
# LLM Open-Source

# Imports
import requests
import numpy as np
import yfinance as yf
from newsapi import NewsApiClient
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.output_parsers import StrOutputParser
from langchain_community.llms.ollama import Ollama

print("\nProjeto 10 - Robô Investidor com IA - Usando LLMs Para Investment Analytics")

# Define a chave da NewsApi
newsapi = NewsApiClient(api_key = 'coloque-aqui-sua-chave')

# Função para obter notícias sobre uma empresa específica
def dsa_coleta_news(company_name):

    # Faz uma requisição à NewsAPI para obter artigos sobre a empresa, em português e ordenados por relevância
    all_articles = newsapi.get_everything(q = company_name,
                                          language = 'pt',
                                          sort_by = 'relevancy',
                                          page_size = 20)
    
    # Inicializa uma lista para armazenar os títulos das notícias
    news_list = []
    
    # Percorre todos os artigos retornados pela API
    for article in all_articles['articles']:
        
        # Extrai o título de cada artigo
        title = article['title']
        
        # Verifica se o título não está vazio e se não contém '[Removed]'
        if title and '[Removed]' not in title:
            
            # Adiciona o título válido à lista de notícias
            news_list.append(title)
    
    # Retorna a lista de títulos de notícias
    return news_list

# Função para obter dados de ações usando a biblioteca yfinance
def dsa_coleta_stock_data(ticker):
    
    # Cria um objeto Ticker para a ação especificada
    stock = yf.Ticker(ticker)
    
    # Obtém dados históricos da ação para o último mês
    data = stock.history(period='1mo')
    
    # Retorna os dados históricos da ação
    return data

# Instanciação do LLM Llama3.2 através do Ollama
llm = Ollama(model = "llama3.2")

# Criação do parser para a saída do modelo de linguagem
output_parser = StrOutputParser()

# Função para analisar o sentimento de uma lista de notícias com Llama
def dsa_analisa_sentimento(news_list):

    # Inicializa uma lista para armazenar os sentimentos das notícias
    sentiments = []
    
    # Percorre cada notícia na lista de notícias
    for news in news_list:

        # Define um prompt para o modelo Llama analisar o sentimento do título da notícia
        prompt = ChatPromptTemplate.from_messages(
            [
                ("system", "Classifique o sentimento do seguinte título de notícia sobre a Apple como 'positivo', 'negativo' ou 'neutro."),
                ("user", "question: {question}")
            ]
        )

        # Definição da cadeia de execução: prompt -> LLM -> output_parser
        chain = prompt | llm | output_parser

        # Executa a cadeia com o prompt fornecido e obtém a resposta 
        response = chain.invoke({'question': news})
        
        # Converte para minúsculo
        sentiment = response.strip().lower()
        
        # Verifica se o sentimento é 'positivo', 'negativo' ou 'neutro' e o adiciona à lista
        if sentiment in ['positivo', 'negativo', 'neutro']:
            sentiments.append(sentiment)
        else:
            # Adiciona 'neutro' se o sentimento não for identificado
            sentiments.append('neutro')
    
    # Retorna a lista de sentimentos
    return sentiments

# Função para converter sentimentos de texto em valores numéricos
def dsa_converte_sentimento(sentiments):
    
    # Inicializa uma lista para armazenar as pontuações numéricas dos sentimentos
    sentiment_scores = []
    
    # Percorre cada sentimento na lista de sentimentos
    for sentiment in sentiments:
        
        # Atribui 1 para 'positivo'
        if 'positivo' in sentiment:
            sentiment_scores.append(1)
        
        # Atribui -1 para 'negativo'
        elif 'negativo' in sentiment:
            sentiment_scores.append(-1)
        
        # Atribui 0 para 'neutro'
        else:
            sentiment_scores.append(0)
    
    # Retorna a lista de pontuações numéricas
    return sentiment_scores

# Função para tomar uma decisão com base nos dados das ações e nos sentimentos
def dsa_toma_decisao(stock_data, sentiment_scores):
    
    # Calcula a variação percentual diária do preço de fechamento das ações
    stock_data['Pct_Change'] = stock_data['Close'].pct_change()
    
    # Obtém a variação percentual mais recente
    recent_change = stock_data['Pct_Change'].iloc[-1]
    
    # Calcula a média dos sentimentos se houver valores na lista
    if sentiment_scores:
        avg_sentiment = np.mean(sentiment_scores)
    else:
        # Define 0 como valor padrão se a lista estiver vazia
        avg_sentiment = 0
    
    # Define a decisão com base nos valores de sentimento e variação de preço
    if avg_sentiment > 0 and recent_change > 0:
        decision = 'Comprar'
    elif avg_sentiment < 0 and recent_change < 0:
        decision = 'Vender'
    else:
        decision = 'Manter'
    
    # Retorna a decisão final
    return decision

# Obtém as notícias sobre a Apple
news = dsa_coleta_news('Apple')

# Exibe o número de notícias obtidas e a lista de notícias
print(f"\nNúmero de notícias obtidas: {len(news)}")
print("\nNotícias:", news)
print("\nO Robô Investidor com IA Está Trabalhando. Aguarde!\n")

# Verifica se há notícias para análise
if not news:
    
    # Define 'Manter' como decisão padrão caso não haja notícias
    print("Nenhuma notícia foi obtida.")
    decision = 'Manter'

else:
    
    # Analisa o sentimento das notícias
    sentiments = dsa_analisa_sentimento(news)
    
    # Exibe os sentimentos analisados
    print("\nSentimentos:", sentiments)
    
    # Converte os sentimentos em valores numéricos
    sentiment_scores = dsa_converte_sentimento(sentiments)
    
    # Toma uma decisão com base nos dados das ações e nos sentimentos
    decision = dsa_toma_decisao(dsa_coleta_stock_data('AAPL'), sentiment_scores)
    
    # Exibe a decisão final
    print(f"\nDecisão de Investimento: {decision}")

print("\nObrigado Por Usar o Robô Investidor com IA da DSA - Volte Sempre!\n")


