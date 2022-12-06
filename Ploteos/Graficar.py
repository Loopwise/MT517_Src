import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Cargar datos
df = pd.read_excel('Results.xlsx', sheet_name='Hoja1')

# Graficar
antihorario = df['Sentido' == 'Antihorario']
horario = df['Sentido' == 'Horario']
plt.plot(df['PWM'], df['V Esp32'], 'o')
plt.plot(df['PWM'], df['V driver'], 'o')
plt.show()