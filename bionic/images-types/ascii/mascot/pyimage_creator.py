from PIL import Image

# Dimensões da imagem
width, height = 128, 128

# Função auxiliar para criar um pixel RGBA
def px(r, g, b, a=255):
    return (r, g, b, a)

# Lista de pixels da imagem completa
pixels = []

for y in range(height):
    for x in range(width):
        color = px(0, 0, 0, 0)  # Fundo transparente

        # Corpo
        if 32 <= x <= 95 and 32 <= y <= 87:
            color = px(0, 120, 220)  # Azul principal do corpo

        # Detalhes do corpo
        if 36 <= x <= 91 and 36 <= y <= 83:
            color = px(0, 140, 240)  # Destaque

        # Cabeça
        if 44 <= x <= 83 and 8 <= y <= 31:
            color = px(0, 160, 255)

        # Olhos
        if (52 <= x <= 58 and 16 <= y <= 22) or (68 <= x <= 74 and 16 <= y <= 22):
            color = px(255, 255, 255)  # Branco dos olhos
        if (54 <= x <= 56 and 18 <= y <= 20) or (70 <= x <= 72 and 18 <= y <= 20):
            color = px(0, 0, 0)  # Pupilas

        # Pernas
        if (40 <= x <= 55 and 88 <= y <= 111) or (72 <= x <= 87 and 88 <= y <= 111):
            color = px(0, 90, 200)

        # Pés
        if (36 <= x <= 59 and 112 <= y <= 119) or (68 <= x <= 91 and 112 <= y <= 119):
            color = px(0, 60, 160)

        # Detalhe de sombra das pernas
        if (48 <= x <= 79 and 88 <= y <= 111):
            color = px(0, 70, 160)

        # Destaques das pernas
        if (42 <= x <= 53 and 88 <= y <= 105) or (74 <= x <= 85 and 88 <= y <= 105):
            color = px(0, 120, 220)

        # Tronco inferior para suavizar a transição
        if 56 <= x <= 71 and 88 <= y <= 95:
            color = px(0, 100, 210)

        pixels.append(color)

# Cria a imagem RGBA
img = Image.new('RGBA', (width, height))
img.putdata(pixels)
img.save('xdroid_mascot.png')
print("Imagem completa do XDroid gerada com sucesso em 'xdroid_mascot.png'!")
