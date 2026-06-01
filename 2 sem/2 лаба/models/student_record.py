from dataclasses import dataclass, field
from typing import List


@dataclass
class StudentRecord:
    full_name: str
    group_number: str
    social_work: List[int] = field(default_factory=list)

    def total_social_work(self) -> int:
        return sum(self.social_work)