from PIL import Image
import os

# Nome do arquivo PNG de entrada e saída
INPUT_FILE = "xdroid_mascot.png"
OUTPUT_FILE = "xdroid_mascot_rendered.png"

def render_mascot(input_file: str, output_file: str):
    """
    Converte o PNG de entrada em uma imagem renderizada de verdade,
    preservando transparência e cores.
    """
    if not os.path.exists(input_file):
        print(f"Erro: Arquivo {input_file} não encontrado!")
        return

    try:
        # Abre a imagem de entrada
        img = Image.open(input_file).convert("RGBA")
        
        # Aqui você pode aplicar filtros, redimensionar ou modificar pixels se quiser
        width, height = img.size
        print(f"Imagem carregada: {width}x{height} pixels")

        # Salva a imagem renderizada
        img.save(output_file)
        print(f"Imagem renderizada salva como: {output_file}")

    except Exception as e:
        print(f"Ocorreu um erro ao processar a imagem: {e}")

if __name__ == "__main__":
    render_mascot(INPUT_FILE, OUTPUT_FILE)
