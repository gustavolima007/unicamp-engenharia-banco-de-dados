/* Prova - Diagrama da empresa desatualizado*/

CREATE DATABASE ERP_DB;

CREATE TABLE Empresa (
    Nome VARCHAR(255),
    CNPJ VARCHAR(18),
    Endereco VARCHAR(255),
    Contato VARCHAR(255),
    Socios TEXT,
    Funcionarios TEXT
);

CREATE TABLE Terreno (
    ID INT,
    Localizacao VARCHAR(255),
    Area DECIMAL(10, 2),
    Tipo_terreno VARCHAR(50),
    Potencial_eolico DECIMAL(10, 2),
    Infraestrutura TEXT,
    Situacao_juridica VARCHAR(50),
    Licenciamento TEXT
);

CREATE TABLE Parque_Eolico (
    ID INT,
    Nome VARCHAR(255),
    Localizacao VARCHAR(255),
    Capacidade_instalada DECIMAL(10, 2),
    Numero_aerogeradores INT,
    Modelo_aerogerador VARCHAR(255),
    Fabricante VARCHAR(255),
    Data_instalacao DATE,
    Situacao_operacional VARCHAR(50),
    Producao_energia TEXT,
    Manutencao TEXT
);

CREATE TABLE Aerogerador (
    ID INT,
    Marca VARCHAR(255),
    Modelo VARCHAR(255),
    Potencia_nominal DECIMAL(10, 2),
    Diametro_rotor DECIMAL(10, 2),
    Altura_mastro DECIMAL(10, 2),
    Data_instalacao DATE,
    Situacao_operacional VARCHAR(50),
    Dados_producao TEXT,
    Manutencao TEXT
);

CREATE TABLE Contrato_Compra_Energia (
    ID INT,
    Comprador VARCHAR(255),
    Fornecedor VARCHAR(255),
    Data_assinatura DATE,
    Prazo_vigencia DATE,
    Quantidade_energia DECIMAL(10, 2),
    Preco_energia DECIMAL(10, 2),
    Forma_pagamento VARCHAR(255),
    Penalidades TEXT
);

CREATE TABLE Outras_Entidades (
    Fornecedor TEXT,
    Cliente TEXT,
    Relatorios TEXT
);
