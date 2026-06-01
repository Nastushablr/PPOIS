from xml.dom.minidom import Document
from xml.sax import make_parser, handler
from models.student_record import StudentRecord


class StudentHandler(handler.ContentHandler):
    def __init__(self):
        super().__init__()
        self.records = []
        self.current_tag = ''
        self.current_full_name = ''
        self.current_group = ''
        self.current_semesters = []
        self.buffer = ''

    def startElement(self, name, attrs):
        self.current_tag = name
        self.buffer = ''
        if name == 'student':
            self.current_full_name = ''
            self.current_group = ''
            self.current_semesters = []

    def characters(self, content):
        self.buffer += content

    def endElement(self, name):
        value = self.buffer.strip()
        if name == 'full_name':
            self.current_full_name = value
        elif name == 'group_number':
            self.current_group = value
        elif name.startswith('semester_'):
            if value:
                self.current_semesters.append(int(value))
        elif name == 'student':
            self.records.append(
                StudentRecord(
                    self.current_full_name,
                    self.current_group,
                    self.current_semesters
                )
            )
        self.current_tag = ''


def save_to_xml(file_path, records):
    doc = Document()
    root = doc.createElement('students')
    doc.appendChild(root)

    for record in records:
        student_node = doc.createElement('student')

        full_name_node = doc.createElement('full_name')
        full_name_node.appendChild(doc.createTextNode(record.full_name))
        student_node.appendChild(full_name_node)

        group_node = doc.createElement('group_number')
        group_node.appendChild(doc.createTextNode(record.group_number))
        student_node.appendChild(group_node)

        social_node = doc.createElement('social_work')
        for i, value in enumerate(record.social_work, start=1):
            sem_node = doc.createElement(f'semester_{i}')
            sem_node.appendChild(doc.createTextNode(str(value)))
            social_node.appendChild(sem_node)
        student_node.appendChild(social_node)

        root.appendChild(student_node)

    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(doc.toprettyxml(indent='  ', encoding=None))


def load_from_xml(file_path):
    parser = make_parser()
    content_handler = StudentHandler()
    parser.setContentHandler(content_handler)
    with open(file_path, 'r', encoding='utf-8') as f:
        parser.parse(f)
    return content_handler.records