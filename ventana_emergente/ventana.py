from flask import Flask
from flask_cors import CORS
from plyer import notification
import tkinter as tk
import tkinter.messagebox

app = Flask(__name__)
CORS(app)

def show_popup(message):
    root = tk.Tk()
    root.withdraw()
    tkinter.messagebox.showinfo("Mensaje", message)
    root.destroy()

@app.route('/test', methods=['GET'])
def presionar_boton():
    print("Botón presionado")
    notification.notify(
        title='Botón Presionado',
        message='Se presionó el botón desde la NodeMCU',
        app_name='Flask Notification'
    )
    show_popup("Hola Mundo")

    return "Botón presionado"

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
