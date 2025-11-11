-- Projeto 5 - Pipeline Automatizado de IA Para Detecção de Fraudes em Transações Financeiras Imobiliárias
-- SQL - Criação do Banco de Dados

-- Deleta o schema se já existir
DROP SCHEMA IF EXISTS projeto5 CASCADE;

-- Cria o schema
CREATE SCHEMA projeto5 AUTHORIZATION dsa;

-- Cria as tabelas

CREATE TABLE projeto5.clientes (
    id_cliente SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100),
    cidade VARCHAR(50),
    estado VARCHAR(2),
    cep VARCHAR(10)
);

CREATE TABLE projeto5.imoveis (
    id_imovel SERIAL PRIMARY KEY,
    endereco VARCHAR(255) NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    estado VARCHAR(50) NOT NULL,
    cep VARCHAR(10),
    descricao TEXT
);

CREATE TABLE projeto5.transacoes_financeiras (
    id_transacao SERIAL PRIMARY KEY,
    id_cliente INT NOT NULL,
    id_imovel INT NOT NULL,
    valor DECIMAL(15, 2) NOT NULL,
    data_transacao DATE NOT NULL,
    tipo_transacao VARCHAR(50),
    status VARCHAR(20),
    FOREIGN KEY (id_cliente) REFERENCES projeto5.clientes(id_cliente),
    FOREIGN KEY (id_imovel) REFERENCES projeto5.imoveis(id_imovel)
);

CREATE TABLE projeto5.historico_transacoes (
    id_historico SERIAL PRIMARY KEY,
    id_transacao INT NOT NULL,
    data_modificacao DATE NOT NULL,
    descricao TEXT,
    FOREIGN KEY (id_transacao) REFERENCES projeto5.transacoes_financeiras(id_transacao)
);

