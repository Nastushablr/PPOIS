import tkinter as tk
from tkinter import ttk, messagebox


class DeleteDialog(tk.Toplevel):
    def __init__(self, parent, groups, on_delete):
        super().__init__(parent)
        self.title('Удаление записей')
        self.resizable(False, False)
        self.on_delete = on_delete

        self.mode_map = {
            'По фамилии или по номеру группы': 'surname_or_group',
            'По фамилии и диапазону общественной работы': 'surname_and_total',
            'По номеру группы и диапазону общественной работы': 'group_and_total'
        }

        self.mode_var = tk.StringVar(value='По фамилии или по номеру группы')
        self.surname_var = tk.StringVar()
        self.group_var = tk.StringVar()
        self.min_var = tk.StringVar()
        self.max_var = tk.StringVar()

        self._build_ui(groups)
        self.transient(parent)
        self.grab_set()

    def _build_ui(self, groups):
        frame = ttk.Frame(self, padding=10)
        frame.pack(fill='both', expand=True)

        ttk.Label(frame, text='Режим:').grid(row=0, column=0, sticky='w', pady=3)
        mode_box = ttk.Combobox(
            frame,
            textvariable=self.mode_var,
            state='readonly',
            width=45,
            values=list(self.mode_map.keys())
        )
        mode_box.grid(row=0, column=1, sticky='w', pady=3)

        ttk.Label(frame, text='Фамилия:').grid(row=1, column=0, sticky='w', pady=3)
        ttk.Entry(frame, textvariable=self.surname_var, width=30).grid(
            row=1, column=1, sticky='w', pady=3
        )

        ttk.Label(frame, text='Группа:').grid(row=2, column=0, sticky='w', pady=3)
        ttk.Combobox(
            frame,
            textvariable=self.group_var,
            values=groups,
            state='readonly',
            width=27
        ).grid(row=2, column=1, sticky='w', pady=3)

        ttk.Label(frame, text='Нижний предел:').grid(row=3, column=0, sticky='w', pady=3)
        ttk.Entry(frame, textvariable=self.min_var, width=15).grid(
            row=3, column=1, sticky='w', pady=3
        )

        ttk.Label(frame, text='Верхний предел:').grid(row=4, column=0, sticky='w', pady=3)
        ttk.Entry(frame, textvariable=self.max_var, width=15).grid(
            row=4, column=1, sticky='w', pady=3
        )

        ttk.Button(frame, text='Удалить', command=self._delete).grid(
            row=5, column=0, columnspan=2, pady=10
        )

    def _parse_int(self, value):
        value = value.strip()
        if value == '':
            return None
        return int(value)

    def _delete(self):
        try:
            selected_mode = self.mode_map[self.mode_var.get()]
            deleted_count = self.on_delete(
                selected_mode,
                self.surname_var.get().strip(),
                self.group_var.get().strip(),
                self._parse_int(self.min_var.get()),
                self._parse_int(self.max_var.get())
            )
        except ValueError:
            messagebox.showerror('Ошибка', 'Границы должны быть целыми числами.')
            return

        if deleted_count > 0:
            messagebox.showinfo('Результат', f'Удалено записей: {deleted_count}')
        else:
            messagebox.showinfo('Результат', 'Подходящих записей не найдено.')
        self.destroy()