import tkinter as tk
from controllers.app_controller import AppController
from models.student_model import StudentModel
from views.main_view import MainView


def main():
    root = tk.Tk()
    model = StudentModel()
    view = MainView(root)
    controller = AppController(model, view)
    view.set_controller(controller)
    controller.refresh_main_table()
    root.mainloop()


if __name__ == '__main__':
    main()