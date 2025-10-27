from PIL import Image

# Arquivo de entrada ASCII
INPUT_FILE = "mascot.txt"
OUTPUT_FILE = "xdroid_mascot_detailed.png"

# Mapeamento detalhado de símbolos para RGB (adicione mais conforme precisar)
UNICODE_DETAILED_COLOR_MAP = {
    '█': (0, 0, 255),        # Azul intenso
    '▓': (0, 0, 200),        # Azul escuro
    '▒': (0, 0, 150),        # Azul médio
    '░': (0, 0, 100),        # Azul claro
    '▌': (50, 50, 255),      # Azul destacado esquerdo
    '▐': (70, 70, 255),      # Azul destacado direito
    '▁': (0, 0, 180),        # Azul barra inferior
    ' ': (0, 0, 0, 0),       # Transparente
    # Adicione outros caracteres e cores conforme seu desenho
}

def unicode_detailed_to_image(input_file: str, output_file: str):
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = [line.rstrip('\n') for line in f if line.strip()]

    height = len(lines)
    width = max(len(line) for line in lines)
    print(f"Tamanho da imagem: {width}x{height}")

    img = Image.new("RGBA", (width, height))
    pixels = img.load()

    for y, line in enumerate(lines):
        for x, char in enumerate(line):
            if char in UNICODE_DETAILED_COLOR_MAP:
                color = UNICODE_DETAILED_COLOR_MAP[char]
                if len(color) == 3:
                    color = (*color, 255)  # Alpha padrão se não tiver
                pixels[x, y] = color
            else:
                # Desconhecido -> transparente
                pixels[x, y] = (0, 0, 0, 0)

    img.save(output_file)
    print(f"Imagem PNG detalhada criada: {output_file}")

if __name__ == "__main__":
    unicode_detailed_to_image(INPUT_FILE, OUTPUT_FILE)
