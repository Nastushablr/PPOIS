import tkinter as tk
from tkinter import ttk, messagebox
from models.student_record import StudentRecord


class RecordDialog(tk.Toplevel):
    def __init__(self, parent, on_save):
        super().__init__(parent)
        self.title('Добавление записи')
        self.resizable(False, False)
        self.on_save = on_save
        self.result = None

        self.full_name_var = tk.StringVar()
        self.group_var = tk.StringVar()
        self.semester_vars = [tk.StringVar(value='0') for _ in range(10)]

        self._build_ui()
        self.transient(parent)
        self.grab_set()

    def _build_ui(self):
        frame = ttk.Frame(self, padding=10)
        frame.pack(fill='both', expand=True)

        ttk.Label(frame, text='ФИО студента:').grid(row=0, column=0,
                                                    sticky='w', pady=3)
        ttk.Entry(frame, textvariable=self.full_name_var,
                  width=40).grid(row=0, column=1, sticky='ew', pady=3)

        ttk.Label(frame, text='Группа:').grid(row=1, column=0,
                                              sticky='w', pady=3)
        ttk.Entry(frame, textvariable=self.group_var,
                  width=20).grid(row=1, column=1, sticky='w', pady=3)

        for i in range(10):
            ttk.Label(frame, text=f'{i + 1} семестр:').grid(
                row=i + 2, column=0, sticky='w', pady=2
            )
            spin = ttk.Spinbox(
                frame, from_=0, to=1000,
                textvariable=self.semester_vars[i], width=10
            )
            spin.grid(row=i + 2, column=1, sticky='w', pady=2)

        buttons = ttk.Frame(frame)
        buttons.grid(row=12, column=0, columnspan=2, pady=10)

        ttk.Button(buttons, text='Сохранить',
                   command=self._save).pack(side='left', padx=5)
        ttk.Button(buttons, text='Отмена',
                   command=self.destroy).pack(side='left', padx=5)

    def _save(self):
        full_name = self.full_name_var.get().strip()
        group_number = self.group_var.get().strip()

        if not full_name:
            messagebox.showerror('Ошибка', 'Введите ФИО студента.')
            return
        if not group_number:
            messagebox.showerror('Ошибка', 'Введите номер группы.')
            return

        try:
            social_work = [int(var.get()) for var in self.semester_vars]
        except ValueError:
            messagebox.showerror(
                'Ошибка', 'Общественная работа должна быть целым числом.'
            )
            return

        record = StudentRecord(full_name, group_number, social_work)
        self.on_save(record)
        self.destroy()