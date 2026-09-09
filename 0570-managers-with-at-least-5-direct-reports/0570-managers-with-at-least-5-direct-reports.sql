# Write your MySQL query statement below
select b.name
from Employee b
join Employee a
on b.id=a.managerId
group by b.id,b.name
having count(a.id)>=5;
