from PIL import Image

# Arquivo de entrada com ASCII Unicode
INPUT_FILE = "mascot.txt"
OUTPUT_FILE = "xdroid_mascot.png"

# Map de caracteres Unicode quadrados para cores (você pode expandir conforme o mascote)
UNICODE_COLOR_MAP = {
    '█': (0, 0, 255),       # Quadrado cheio azul
    '▓': (0, 0, 200),       # Azul mais escuro
    '▒': (0, 0, 150),       # Azul médio
    '░': (0, 0, 100),       # Azul claro
    ' ': (0, 0, 0, 0),      # Transparente
    # Você pode adicionar outros símbolos e cores aqui
}

def unicode_to_image(input_file: str, output_file: str):
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = [line.rstrip('\n') for line in f if line.strip()]

    height = len(lines)
    width = max(len(line) for line in lines)
    print(f"Tamanho da imagem: {width}x{height}")

    img = Image.new("RGBA", (width, height))
    pixels = img.load()

    for y, line in enumerate(lines):
        for x, char in enumerate(line):
            if char in UNICODE_COLOR_MAP:
                color = UNICODE_COLOR_MAP[char]
                if len(color) == 3:
                    color = (*color, 255)  # Adiciona alpha
                pixels[x, y] = color
            else:
                pixels[x, y] = (0, 0, 0, 0)  # Transparente se caractere desconhecido

    img.save(output_file)
    print(f"Imagem PNG criada: {output_file}")

if __name__ == "__main__":
    unicode_to_image(INPUT_FILE, OUTPUT_FILE)
