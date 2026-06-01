import tkinter as tk
from tkinter import ttk


class MainView:
    def __init__(self, root):
        self.root = root
        self.root.title('Студенты и общественная работа')
        self.root.geometry('1200x650')
        self.controller = None
        self.page_size_var = tk.StringVar(value='10')
        self.info_var = tk.StringVar(value='Страница 1/1. Показано 0 из 0.')
        self._build_ui()

    def set_controller(self, controller):
        self.controller = controller

    def _build_ui(self):
        self._build_menu()
        self._build_toolbar()
        self._build_table()
        self._build_pagination()

    def _build_menu(self):
        menu_bar = tk.Menu(self.root)

        file_menu = tk.Menu(menu_bar, tearoff=0)
        file_menu.add_command(label='Открыть XML', command=lambda: self.controller.load_xml())
        file_menu.add_command(label='Сохранить XML', command=lambda: self.controller.save_xml())
        file_menu.add_separator()
        file_menu.add_command(label='Выход', command=self.root.quit)
        menu_bar.add_cascade(label='Файл', menu=file_menu)

        actions_menu = tk.Menu(menu_bar, tearoff=0)
        actions_menu.add_command(label='Добавить запись',
                                 command=lambda: self.controller.open_add_dialog())
        actions_menu.add_command(label='Поиск',
                                 command=lambda: self.controller.open_search_dialog())
        actions_menu.add_command(label='Удаление',
                                 command=lambda: self.controller.open_delete_dialog())
        menu_bar.add_cascade(label='Действия', menu=actions_menu)

        self.root.config(menu=menu_bar)

    def _build_toolbar(self):
        toolbar = ttk.Frame(self.root, padding=5)
        toolbar.pack(fill='x')

        ttk.Button(toolbar, text='Добавить',
                   command=lambda: self.controller.open_add_dialog()).pack(side='left', padx=2)
        ttk.Button(toolbar, text='Поиск',
                   command=lambda: self.controller.open_search_dialog()).pack(side='left', padx=2)
        ttk.Button(toolbar, text='Удалить',
                   command=lambda: self.controller.open_delete_dialog()).pack(side='left', padx=2)
        ttk.Button(toolbar, text='Открыть XML',
                   command=lambda: self.controller.load_xml()).pack(side='left', padx=10)
        ttk.Button(toolbar, text='Сохранить XML',
                   command=lambda: self.controller.save_xml()).pack(side='left', padx=2)

    def _build_table(self):
        frame = ttk.Frame(self.root, padding=10)
        frame.pack(fill='both', expand=True)

        columns = ['full_name', 'group_number'] + [f'sem_{i}' for i in range(1, 11)] + ['total']
        self.tree = ttk.Treeview(frame, columns=columns, show='headings')

        self.tree.heading('full_name', text='ФИО студента')
        self.tree.heading('group_number', text='Группа')
        self.tree.column('full_name', width=220)
        self.tree.column('group_number', width=90)

        for i in range(1, 11):
            column_name = f'sem_{i}'
            self.tree.heading(column_name, text=f'{i} сем')
            self.tree.column(column_name, width=60, anchor='center')

        self.tree.heading('total', text='Итого')
        self.tree.column('total', width=80, anchor='center')

        scrollbar = ttk.Scrollbar(frame, orient='vertical', command=self.tree.yview)
        self.tree.configure(yscrollcommand=scrollbar.set)

        self.tree.pack(side='left', fill='both', expand=True)
        scrollbar.pack(side='right', fill='y')

    def _build_pagination(self):
        bottom = ttk.Frame(self.root, padding=10)
        bottom.pack(fill='x')

        ttk.Button(bottom, text='<<',
                   command=lambda: self.controller.first_page()).pack(side='left', padx=2)
        ttk.Button(bottom, text='<',
                   command=lambda: self.controller.prev_page()).pack(side='left', padx=2)
        ttk.Button(bottom, text='>',
                   command=lambda: self.controller.next_page()).pack(side='left', padx=2)
        ttk.Button(bottom, text='>>',
                   command=lambda: self.controller.last_page()).pack(side='left', padx=2)

        ttk.Label(bottom, text='Записей на странице:').pack(side='left', padx=(15, 5))
        box = ttk.Combobox(bottom, textvariable=self.page_size_var,
                           state='readonly', width=5, values=['5', '10', '20'])
        box.pack(side='left')
        box.bind('<<ComboboxSelected>>',
                 lambda event: self.controller.change_page_size(self.page_size_var.get()))

        ttk.Label(bottom, textvariable=self.info_var).pack(side='right')

    def show_records(self, records, current_page, total_pages, current_count, total_count):
        for item in self.tree.get_children():
            self.tree.delete(item)

        for record in records:
            row = [record.full_name, record.group_number] + record.social_work + \
                  [record.total_social_work()]
            self.tree.insert('', 'end', values=row)

        self.info_var.set(
            f'Страница {current_page}/{total_pages}. '
            f'Показано {current_count} из {total_count}.'
        )