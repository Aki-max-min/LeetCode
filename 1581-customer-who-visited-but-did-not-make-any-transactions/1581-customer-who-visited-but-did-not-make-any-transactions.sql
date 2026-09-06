# Write your MySQL query statement below
select Visits.customer_id,COUNT(*) AS count_no_trans
from Visits
left join Transactions
on Visits.visit_id=Transactions.visit_id
WHERE Transactions.transaction_id IS NULL
group by Visits.customer_id;
