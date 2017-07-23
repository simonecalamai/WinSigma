select * from certificati c left join verbali v on v.codice = c.verbale where c.codice = 115027
select * from certificati c left join verbali v on v.codice = c.verbale where c.codice = 115065

select * from certificati c left join verbali v on v.codice = c.verbale where c.codice = 115073

select sperimentatore from serie where NuovoCertificato = 1 and certificato = 115027

select * from operatori where REPLACE(CONCAT(Titolo, Nome, Cognome), ' ', '') = REPLACE('Dott.  Ing. Marco Pompucci', ' ', '')
select * from operatori where REPLACE(CONCAT(IFNULL(Titolo, ''), Nome, Cognome), ' ', '') = REPLACE('Geom. Enzo Ripellino', ' ', '')
select REPLACE(CONCAT(Titolo, Nome, Cognome), ' ', '') from operatori 


select o.Codice, o.Titolo, o.Nome, o.Cognome from serie s left join operatori o on REPLACE(CONCAT(IFNULL(o.Titolo, ''), o.Nome, o.Cognome), ' ', '') = REPLACE('Geom. Enzo Ripellino', ' ', '')
where NuovoCertificato = 1 and certificato = 115027

alter table operatori add column Sigla varchar(8) DEFAULT ''

select * from operatori

select * from serie where NuovoCertificato = 1 order by DataProva desc
