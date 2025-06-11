import pandas as pd

# Caminho do seu Excel original
arquivo = r"C:\Users\User\Documents\Unesp\Trabalho Estrutura\archive\measures_v2.csv"

# Lê o Excel (primeira planilha)
df = pd.read_csv(arquivo)

# Mostra colunas disponíveis para você ver
print("Colunas disponíveis:")
print(df.columns.tolist())

# Filtrar só as colunas importantes (ajustar conforme necessário)
colunas_utilizadas = [
    "torque", "ambient", "coolant", "motor_speed", "stator_yoke", "stator_winding"
]


# Filtra e remove nulos
df_filtrado = df[colunas_utilizadas].copy()
df_filtrado.dropna(inplace=True)

# Reduz para 30.000 amostras
df_final = df_filtrado.head(30000)

# Salva CSV final na subpasta "data"
df_final.to_csv("data/motor_dados_tratado.csv", index=False)
print("✅ Arquivo tratado salvo como: data/motor_dados_tratado.csv")
