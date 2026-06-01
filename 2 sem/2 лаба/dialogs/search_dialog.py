import tkinter as tk
from tkinter import ttk, messagebox
from utils.pagination import PaginationHelper


class SearchDialog(tk.Toplevel):
    def __init__(self, parent, groups, on_search):
        super().__init__(parent)
        self.title('Поиск записей')
        self.geometry('1000x500')
        self.on_search = on_search
        self.pagination = PaginationHelper(10)
        self.search_result = []

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
        self.page_size_var = tk.StringVar(value='10')

        self._build_ui(groups)
        self.transient(parent)
        self.grab_set()

    def _build_ui(self, groups):
        top = ttk.Frame(self, padding=10)
        top.pack(fill='x')

        ttk.Label(top, text='Режим:').grid(row=0, column=0, sticky='w')
        modes = ttk.Combobox(
            top,
            textvariable=self.mode_var,
            state='readonly',
            width=45,
            values=list(self.mode_map.keys())
        )
        modes.grid(row=0, column=1, sticky='w', padx=5, pady=3)

        ttk.Label(top, text='Фамилия:').grid(row=1, column=0, sticky='w')
        ttk.Entry(top, textvariable=self.surname_var, width=30).grid(
            row=1, column=1, sticky='w', padx=5, pady=3
        )

        ttk.Label(top, text='Группа:').grid(row=2, column=0, sticky='w')
        group_box = ttk.Combobox(
            top,
            textvariable=self.group_var,
            values=groups,
            state='readonly',
            width=27
        )
        group_box.grid(row=2, column=1, sticky='w', padx=5, pady=3)

        ttk.Label(top, text='Нижний предел:').grid(row=3, column=0, sticky='w')
        ttk.Entry(top, textvariable=self.min_var, width=15).grid(
            row=3, column=1, sticky='w', padx=5, pady=3
        )

        ttk.Label(top, text='Верхний предел:').grid(row=4, column=0, sticky='w')
        ttk.Entry(top, textvariable=self.max_var, width=15).grid(
            row=4, column=1, sticky='w', padx=5, pady=3
        )

        ttk.Button(top, text='Найти', command=self._run_search).grid(
            row=5, column=1, sticky='w', padx=5, pady=5
        )

        table_frame = ttk.Frame(self, padding=(10, 0, 10, 10))
        table_frame.pack(fill='both', expand=True)

        columns = ['full_name', 'group_number', 'total']
        self.tree = ttk.Treeview(table_frame, columns=columns, show='headings', height=12)
        self.tree.heading('full_name', text='ФИО')
        self.tree.heading('group_number', text='Группа')
        self.tree.heading('total', text='Всего общественной работы')
        self.tree.column('full_name', width=350)
        self.tree.column('group_number', width=120)
        self.tree.column('total', width=180)
        self.tree.pack(fill='both', expand=True)

        bottom = ttk.Frame(self, padding=10)
        bottom.pack(fill='x')

        ttk.Button(bottom, text='<<', command=self._first_page).pack(side='left', padx=2)
        ttk.Button(bottom, text='<', command=self._prev_page).pack(side='left', padx=2)
        ttk.Button(bottom, text='>', command=self._next_page).pack(side='left', padx=2)
        ttk.Button(bottom, text='>>', command=self._last_page).pack(side='left', padx=2)

        ttk.Label(bottom, text='Записей на странице:').pack(side='left', padx=(15, 5))
        page_sizes = ttk.Combobox(
            bottom,
            textvariable=self.page_size_var,
            state='readonly',
            width=5,
            values=['5', '10', '20']
        )
        page_sizes.pack(side='left')
        page_sizes.bind('<<ComboboxSelected>>', lambda event: self._change_page_size())

        self.info_label = ttk.Label(bottom, text='Страница 1/1. Показано 0 из 0.')
        self.info_label.pack(side='right')

    def _parse_int(self, value):
        value = value.strip()
        if value == '':
            return None
        return int(value)

    def _run_search(self):
        try:
            selected_mode = self.mode_map[self.mode_var.get()]
            result = self.on_search(
                selected_mode,
                self.surname_var.get().strip(),
                self.group_var.get().strip(),
                self._parse_int(self.min_var.get()),
                self._parse_int(self.max_var.get())
            )
        except ValueError:
            messagebox.showerror('Ошибка', 'Границы должны быть целыми числами.')
            return

        self.search_result = result
        self.pagination.page = 1
        self._refresh_table()

    def _change_page_size(self):
        self.pagination.set_page_size(int(self.page_size_var.get()))
        self._refresh_table()

    def _refresh_table(self):
        for item in self.tree.get_children():
            self.tree.delete(item)

        page_items = self.pagination.get_page_items(self.search_result)
        for record in page_items:
            self.tree.insert(
                '',
                'end',
                values=(record.full_name, record.group_number, record.total_social_work())
            )

        total_items = len(self.search_result)
        total_pages = self.pagination.get_total_pages(total_items)
        current_count = len(page_items)
        self.info_label.config(
            text=f'Страница {self.pagination.page}/{total_pages}. '
                 f'Показано {current_count} из {total_items}.'
        )

    def _first_page(self):
        self.pagination.page = 1
        self._refresh_table()

    def _prev_page(self):
        if self.pagination.page > 1:
            self.pagination.page -= 1
        self._refresh_table()

    def _next_page(self):
        total_pages = self.pagination.get_total_pages(len(self.search_result))
        if self.pagination.page < total_pages:
            self.pagination.page += 1
        self._refresh_table()

    def _last_page(self):
        self.pagination.page = self.pagination.get_total_pages(len(self.search_result))
        self._refresh_table()