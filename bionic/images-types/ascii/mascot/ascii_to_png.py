from PIL import Image

# Arquivo de entrada com ASCII + RGB decimal
INPUT_FILE = "mascot.txt"
OUTPUT_FILE = "xdroid_mascot.png"

def parse_rgb_line(line: str):
    """
    Converte uma linha do arquivo (formato: R,G,B) em tupla RGB
    """
    parts = line.strip().split(',')
    if len(parts) != 3:
        raise ValueError(f"Linha inválida: {line}")
    return tuple(int(p) for p in parts)

def ascii_to_image(input_file: str, output_file: str):
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = [l.strip() for l in f if l.strip()]

    height = len(lines)
    width = len(lines[0].split())  # Assume que cada pixel é separado por espaço
    print(f"Tamanho da imagem: {width}x{height}")

    img = Image.new("RGBA", (width, height))
    pixels = img.load()

    for y, line in enumerate(lines):
        for x, rgb_str in enumerate(line.split()):
            r, g, b = parse_rgb_line(rgb_str)
            pixels[x, y] = (r, g, b, 255)  # Alpha 255 (opaco)

    img.save(output_file)
    print(f"Imagem PNG criada: {output_file}")

if __name__ == "__main__":
    ascii_to_image(INPUT_FILE, OUTPUT_FILE)
