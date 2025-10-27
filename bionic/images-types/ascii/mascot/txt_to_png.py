from PIL import Image

# Nome do arquivo de entrada e saída
INPUT_FILE = "mascot.txt"
OUTPUT_FILE = "xdroid_mascot.png"

# Mapeamento de caracteres para cores (RGB)
UNICODE_DETAILED_COLOR_MAP = {
    '█': (0, 0, 255, 255),   # Azul intenso
    '▓': (0, 0, 200, 255),   # Azul médio
    '▒': (0, 0, 150, 255),   # Azul claro
    '░': (0, 0, 100, 255),   # Azul mais claro
    ' ': (0, 0, 0, 0),       # Transparente
}

# Lê o arquivo de texto
with open(INPUT_FILE, 'r', encoding='utf-8') as f:
    lines = [line.rstrip('\n') for line in f]

height = len(lines)
width = max(len(line) for line in lines)

# Cria uma imagem RGBA
img = Image.new("RGBA", (width, height), (0, 0, 0, 0))
pixels = img.load()

# Preenche os pixels com base no mapa de caracteres
for y, line in enumerate(lines):
    for x, char in enumerate(line):
        color = UNICODE_DETAILED_COLOR_MAP.get(char, (0, 0, 0, 0))
        pixels[x, y] = color

# Salva a imagem final
img.save(OUTPUT_FILE)
print(f"Imagem gerada com sucesso: {OUTPUT_FILE}")
