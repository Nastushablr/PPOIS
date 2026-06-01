class PaginationHelper:
    def __init__(self, page_size=10):
        self.page = 1
        self.page_size = page_size

    def set_page_size(self, size):
        self.page_size = max(1, int(size))
        self.page = 1

    def set_page(self, page, total_items):
        max_page = self.get_total_pages(total_items)
        self.page = max(1, min(page, max_page))

    def get_total_pages(self, total_items):
        if total_items == 0:
            return 1
        return (total_items + self.page_size - 1) // self.page_size

    def get_page_items(self, items):
        start = (self.page - 1) * self.page_size
        end = start + self.page_size
        return items[start:end]