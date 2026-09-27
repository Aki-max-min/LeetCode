# Write your MySQL query statement below
select a.name as Employee
from Employee a
join Employee b
on b.id=a.managerId
where a.salary>b.salary;
