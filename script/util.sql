show tables;
show columns from Fatture;
alter table Fatture add column fPA tinyint DEFAULT 0;
alter table Fatture add column fIVADiff tinyint DEFAULT 0;
create table FattureNew select * from Fatture;

