from tkinter import filedialog, messagebox
from dialogs.record_dialog import RecordDialog
from dialogs.search_dialog import SearchDialog
from dialogs.delete_dialog import DeleteDialog
from utils.pagination import PaginationHelper
from utils.xml_storage import save_to_xml, load_from_xml
from views.main_view import MainView


class AppController:
    def __init__(self, model, view: MainView):
        self.model = model
        self.view = view
        self.pagination = PaginationHelper(10)

    def open_add_dialog(self):
        RecordDialog(self.view.root, self._add_record)

    def _add_record(self, record):
        self.model.add_record(record)
        self.refresh_main_table()

    def open_search_dialog(self):
        groups = self.model.get_groups()
        SearchDialog(self.view.root, groups, self.model.search)

    def open_delete_dialog(self):
        groups = self.model.get_groups()
        DeleteDialog(self.view.root, groups, self._delete_records)

    def _delete_records(self, mode, surname, group_number, min_total, max_total):
        deleted = self.model.delete_by_condition(mode, surname, group_number, min_total, max_total)
        self.refresh_main_table()
        return deleted

    def refresh_main_table(self):
        all_records = self.model.get_all_records()
        page_records = self.pagination.get_page_items(all_records)
        total_count = len(all_records)
        total_pages = self.pagination.get_total_pages(total_count)
        current_count = len(page_records)
        self.view.show_records(page_records, self.pagination.page, total_pages, current_count, total_count)

    def first_page(self):
        self.pagination.page = 1
        self.refresh_main_table()

    def prev_page(self):
        if self.pagination.page > 1:
            self.pagination.page -= 1
        self.refresh_main_table()

    def next_page(self):
        total_pages = self.pagination.get_total_pages(len(self.model.get_all_records()))
        if self.pagination.page < total_pages:
            self.pagination.page += 1
        self.refresh_main_table()

    def last_page(self):
        self.pagination.page = self.pagination.get_total_pages(len(self.model.get_all_records()))
        self.refresh_main_table()

    def change_page_size(self, size):
        self.pagination.set_page_size(int(size))
        self.refresh_main_table()

    def save_xml(self):
        file_path = filedialog.asksaveasfilename(
            defaultextension='.xml',
            filetypes=[('XML files', '*.xml')]
        )
        if not file_path:
            return
        try:
            save_to_xml(file_path, self.model.get_all_records())
            messagebox.showinfo('Успех', 'Данные сохранены в XML.')
        except Exception as e:
            messagebox.showerror('Ошибка', f'Не удалось сохранить файл: {e}')

    def load_xml(self):
        file_path = filedialog.askopenfilename(
            filetypes=[('XML files', '*.xml')]
        )
        if not file_path:
            return
        try:
            records = load_from_xml(file_path)
            self.model.load_records(records)
            self.pagination.page = 1
            self.refresh_main_table()
            messagebox.showinfo('Успех', 'Данные загружены из XML.')
        except Exception as e:
            messagebox.showerror('Ошибка', f'Не удалось загрузить файл: {e}')