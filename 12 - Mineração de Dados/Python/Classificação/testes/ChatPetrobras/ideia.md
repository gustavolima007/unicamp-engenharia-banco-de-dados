Gerado no GPT-4o Mini

# Exercícios de Classificação de Dados com NumPy, Pandas e Scikit-Learn

## 1. Introdução ao NumPy
- **Exercício 1:** Importe a biblioteca NumPy e crie um array unidimensional com os valores de vendas globais (Global_Sales) do dataset "vgsales.csv".
- **Exercício 2:** Calcule a média, mediana e desvio padrão das vendas globais utilizando funções do NumPy.

## 2. Manipulação de Dados com Pandas
- **Exercício 3:** Importe a biblioteca Pandas e carregue o dataset "vgsales.csv" em um DataFrame.
- **Exercício 4:** Exiba as primeiras 10 linhas do DataFrame e descreva as colunas presentes.
- **Exercício 5:** Verifique se há valores ausentes no DataFrame e, se houver, conte quantos são.

## 3. Limpeza de Dados
- **Exercício 6:** Remova as linhas que contêm valores ausentes do DataFrame.
- **Exercício 7:** Crie uma nova coluna chamada "Total_Sales" que seja a soma das vendas em todas as regiões (NA_Sales, EU_Sales, JP_Sales, Other_Sales).

## 4. Análise Exploratória de Dados
- **Exercício 8:** Utilize o método `groupby` do Pandas para calcular as vendas médias por gênero (Genre) e exiba os resultados em ordem decrescente.
- **Exercício 9:** Crie um gráfico de barras que mostre as vendas totais por plataforma (Platform) utilizando a biblioteca Matplotlib.

## 5. Preparação para Classificação
- **Exercício 10:** Converta a coluna "Genre" em variáveis categóricas utilizando o método `pd.get_dummies()`.
- **Exercício 11:** Separe o DataFrame em variáveis independentes (X) e dependentes (y), onde y será a coluna "Global_Sales" e X será o restante das colunas.

## 6. Divisão de Dados
- **Exercício 12:** Divida os dados em conjuntos de treinamento e teste utilizando a função `train_test_split` do Scikit-Learn, com 80% dos dados para treinamento e 20% para teste.

## 7. Classificação com Scikit-Learn
- **Exercício 13:** Importe o classificador `RandomForestClassifier` do Scikit-Learn e treine o modelo com os dados de treinamento.
- **Exercício 14:** Faça previsões com o conjunto de teste e calcule a acurácia do modelo utilizando a função `accuracy_score`.

## 8. Avaliação do Modelo
- **Exercício 15:** Crie uma matriz de confusão para visualizar o desempenho do modelo e discuta os resultados obtidos.
