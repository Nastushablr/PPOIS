from models.student_record import StudentRecord


class StudentModel:
    def __init__(self):
        self.records = []

    def add_record(self, record: StudentRecord):
        self.records.append(record)

    def get_all_records(self):
        return list(self.records)

    def clear(self):
        self.records.clear()

    def load_records(self, records):
        self.records = list(records)

    def get_groups(self):
        groups = sorted({record.group_number for record in self.records})
        return groups

    def search(self, mode, surname='', group_number='', min_total=None, max_total=None):
        result = []
        for record in self.records:
            surname_value = self._get_surname(record.full_name)
            total = record.total_social_work()

            ok = False
            if mode == 'surname_or_group':
                ok = (surname and surname_value.lower() == surname.lower()) or \
                     (group_number and record.group_number == group_number)
            elif mode == 'surname_and_total':
                ok = surname and surname_value.lower() == surname.lower() and \
                     self._check_total(total, min_total, max_total)
            elif mode == 'group_and_total':
                ok = group_number and record.group_number == group_number and \
                     self._check_total(total, min_total, max_total)

            if ok:
                result.append(record)
        return result

    def delete_by_condition(self, mode, surname='', group_number='', min_total=None, max_total=None):
        found = self.search(mode, surname, group_number, min_total, max_total)
        count = len(found)
        if count == 0:
            return 0

        found_ids = {id(item) for item in found}
        self.records = [record for record in self.records if id(record) not in found_ids]
        return count

    def _get_surname(self, full_name):
        parts = full_name.split()
        return parts[0] if parts else ''

    def _check_total(self, total, min_total, max_total):
        if min_total is not None and total < min_total:
            return False
        if max_total is not None and total > max_total:
            return False
        return True