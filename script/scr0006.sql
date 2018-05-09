--------------------------------------------------
-- VERSIONE 4.6.0
--------------------------------------------------

-- aggiunta campo tipi_certificato.Attivo
alter table TIPI_CERTIFICATO add column Attivo INT DEFAULT 1;
update TIPI_CERTIFICATO set Attivo = 0 where Codice in (1, 2, 4, 6, 8, 10);

-- nuovo certificato CompressioneCubiDM2018
INSERT INTO `TIPI_CERTIFICATO` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (16, 'Prove su cubi D.M. 2018', NULL, 'CertificatoCubi2018.prn', 'Cubetti2018.prn', 'CompressioneCubiDM2018', 'Compressione su cubi', NULL, NULL, 'Lunghezza(mm)', 150, 'Larghezza(mm)', 150, 'Altezza(mm)', 150, 6, 28, 12, 0, 'Verbali.prn', 1);

-- configurazione servizi certificato CompressioneCubiDM2018
update SERVIZI_LISTINO set certificato4 = 16, prove4 = 1 where categoria = 548 and (certificato = 12 or certificato2 = 12 or certificato3 = 12 or certificato4 = 12)

-- associazione tipi materiali al certificato CompressioneCubiDM2018
update TIPI_MATERIALE set TipoCertificato2 = 16 where TipoCertificato = 12
update TIPI_MATERIALE set TipoCertificato3 = 16 where TipoCertificato2 = 12
update TIPI_MATERIALE set TipoCertificato4 = 16 where TipoCertificato3 = 12

-- campo serie.Sigla 16 caratteri
ALTER TABLE SERIE MODIFY Sigla VARCHAR(16);

-- aggiunta campo serie.Sigla2
alter table SERIE add column Sigla2 varchar(16) DEFAULT '';


-- nuovo certificato BarreB450 DM2018
INSERT INTO `TIPI_CERTIFICATO` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (17, 'Prove su barre da c.a. B450 D.M. 2018', NULL, 'CertificatoBarreB450_2018.prn', 'AcciaioCAB450_2018.prn', 'TrazionePiegamentoBarreB450_2018', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 11, 0, 'Verbali.prn', 1);

update SERVIZI_LISTINO set certificato2 = 17, prove2 = 1 where categoria = 551 and ID in ('DA01', 'DA02', 'DA03', 'DA04', 'DA05', 'DA09', 'DA10')

update TIPI_MATERIALE set TipoCertificato4 = 17 where (TipoCertificato = 11 or TipoCertificato2 = 11 or TipoCertificato3 = 11)


--------------------------------------------------
-- VERSIONE 4.6.1
--------------------------------------------------

-- correzione ID certificato Cubi da 16 a 18
update TIPI_CERTIFICATO set Codice = 18 where Codice = 16

select * from TIPI_MATERIALE where TipoCertificato = 16
select * from TIPI_MATERIALE where TipoCertificato2 = 16
select * from TIPI_MATERIALE where TipoCertificato3 = 16
select * from TIPI_MATERIALE where TipoCertificato4 = 16

update TIPI_MATERIALE set TipoCertificato = 18 where TipoCertificato = 16
update TIPI_MATERIALE set TipoCertificato2 = 18 where TipoCertificato2 = 16
update TIPI_MATERIALE set TipoCertificato3 = 18 where TipoCertificato3 = 16
update TIPI_MATERIALE set TipoCertificato4 = 18 where TipoCertificato4 = 16

select * from CERTIFICATI where TipoCertificato = 16
update certificati set TipoCertificato = 18 where TipoCertificato = 16

select * from SERVIZI_LISTINO where Certificato = 16 Or Certificato2 = 16 or certificato3 = 16 or certificato4 = 16
update SERVIZI_LISTINO set Certificato4 = 18 where Certificato4 = 16

update SERIE set TipoCertificato = 18 where TipoCertificato = 16

-- nuovo certificato RetiElettrosaldateDM2018   (era 15)
INSERT INTO `TIPI_CERTIFICATO` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (19, 'Prove su reti elettrosaldate D.M. 2018', NULL, 'CertificatoReti2018.prn', 'MinutaReti2018.prn', 'TrazioneRetiDM2018', 'Trazione su reti', 'Distacco sul nodo', NULL, 'Diametro(mm)', NULL, NULL, NULL, NULL, NULL, 6, 0, 15, 0, 'Verbali.prn', 1);

-- configurazione servizi certificato RetiElettrosaldateDM2018
update SERVIZI_LISTINO set certificato3 = 19, prove3 = prove2 where categoria = 551 and certificato2 = 15

-- associazione tipi materiali al certificato RetiElettrosaldateDM2018
update TIPI_MATERIALE set TipoCertificato3 = 19 where TipoCertificato2 = 15


-- aggiunta campi servizi_listino.Certificato5, servizi_listino.Prove5 
alter table SERVIZI_LISTINO add column Certificato5 int DEFAULT 0;
alter table SERVIZI_LISTINO add column Prove5 smallint DEFAULT 0;
-- aggiunta campo tipi_materiale.TipoCertificato5 
alter table TIPI_MATERIALE add column TipoCertificato5 int DEFAULT 0;


-- nuovo certificato CentroTrasformazioneDM2018   (era 13)
INSERT INTO `TIPI_CERTIFICATO` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (20, 'Prova su barre Centro Trasformazione D.M. 2018', NULL, 'CertificatoBarreCT2018.prn', 'AcciaioCT2018.prn', 'TrazionePiegamentoBarreCTDM2018', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 13, 0, 'VerbaleCT.prn', 1);

-- configurazione servizi certificato RetiElettrosaldateDM2018
update SERVIZI_LISTINO set certificato = 3, certificato4 = 13 where categoria  = 551 and ID = 'DA05'

-- associazioni servizi listino a certificato 20
update SERVIZI_LISTINO set certificato5 = 20, prove5 = prove4 where categoria = 551 and certificato4 = 13
select * from SERVIZI_LISTINO where certificato4 = 13 and categoria = 551

-- associazione tipi materiali al certificato RetiElettrosaldateDM2018
update TIPI_MATERIALE set TipoCertificato5 = 20 where TipoCertificato3 = 13
select * from TIPI_MATERIALE where TipoCertificato = 10