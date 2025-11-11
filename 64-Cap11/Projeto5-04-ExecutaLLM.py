# Projeto 5 - Pipeline Automatizado de IA Para Detecção de Fraudes em Transações Financeiras Imobiliárias
# Python - Pipeline de Extração de Insights com LLM

# Imports
import csv
import psycopg2
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.output_parsers import StrOutputParser
from langchain_community.llms.ollama import Ollama

# Instanciação do LLM Llama3 através do Ollama
llm = Ollama(model = "llama3")

# Criação do parser para a saída do modelo de linguagem
output_parser = StrOutputParser()

# Função para gerar texto baseado nos dados do PostgreSQL
def dsa_gera_insights():

    # Conecta ao banco de dados PostgreSQL com as credenciais fornecidas
    conn = psycopg2.connect(
        dbname="dsadb",
        user="dsa",
        password="",
        host="localhost",
        port="5553"
    )

    # Cria um cursor para executar comandos SQL
    cursor = conn.cursor()
    
    # Define a consulta SQL para obter dados dos clientes, imóveis e transações
    query = """
        SELECT t.id_transacao AS id_transacao, 
               c.nome AS cliente, 
               i.descricao AS imovel_descricao,
               t.valor AS valor_imovel, 
               t.data_transacao AS data_transacao, 
               t.tipo_transacao AS tipo_transacao, 
               t.status AS status, 
               h.data_modificacao AS data_modificacao, 
               h.descricao AS historico_descricao
        FROM projeto5.transacoes_financeiras t
        JOIN projeto5.clientes c ON t.id_cliente = c.id_cliente
        JOIN projeto5.imoveis i ON t.id_imovel = i.id_imovel
        JOIN projeto5.historico_transacoes h ON t.id_transacao = h.id_transacao
        WHERE t.valor > 1000000  -- valor alto pode ser indicativo de fraude
           OR (t.status = 'Concluída' AND h.descricao LIKE '%Cancelamento%')  -- cancelamento após conclusão pode ser suspeito
           OR EXISTS (  -- verifica se há múltiplas transações para o mesmo imóvel em um curto período de tempo
                        SELECT 1 FROM projeto5.transacoes_financeiras t2
                        WHERE t2.id_imovel = t.id_imovel
                          AND t2.id_transacao != t.id_transacao
                          AND ABS(EXTRACT(DAY FROM AGE(t2.data_transacao, t.data_transacao))) < 30)
        ORDER BY t.data_transacao DESC;
    """
    
    # Executa a consulta SQL
    cursor.execute(query)

    # Obtém todos os resultados da consulta
    rows = cursor.fetchall()
    
    # Inicializa uma lista para armazenar os insights
    insights = []

    # Criação do template de prompt para o chatbot 
    prompt = ChatPromptTemplate.from_messages(
        [
            ("system", "Você é um analista imobiliário especializado. Analise os dados e forneça feedback em português do Brasil sobre detecção de fraudes em transações financeiras imobiliárias."),
            ("user", "question: {question}")
        ]
    )

    # Definição da cadeia de execução: prompt -> LLM -> output_parser
    chain = prompt | llm | output_parser

    # Itera sobre as linhas de resultados
    for row in rows:
        
        # Desempacota os valores de cada linha
        id_transacao, cliente, imovel_descricao, valor_imovel, data_transacao, tipo_transacao, status, data_modificacao, historico_descricao = row
        
        # Cria o prompt para o LLM com base nos dados 
        consulta = f"ID_Transação {id_transacao} Nome do Cliente {cliente} Descrição do Imóvel {imovel_descricao} Valor do Imóvel ${valor_imovel:.2f} Data da Transação {data_transacao} Tipo da Transação {tipo_transacao} Status {status} Data Modificação {data_modificacao} Descrição do Histórico {historico_descricao}."
        
        # Gera o texto de insight usando o LLM
        response = chain.invoke({'question': consulta})
        
        # Adiciona o texto gerado à lista de insights
        insights.append(response)
    
    # Fecha a conexão com o banco de dados
    conn.close()

    # Salva os insights em um arquivo CSV
    with open('projeto5-analise.csv', mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["Insight"])
        for insight in insights:
            writer.writerow([insight])

    # Retorna a lista de insights
    return insights

# Gera insights chamando a função definida
insights = dsa_gera_insights()

# Imprime cada insight gerado
for insight in insights:
    print(insight)





