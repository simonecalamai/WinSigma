--------------------------------------------------
-- VERSIONE 4.6.0
--------------------------------------------------
-- nuovo certificato CompressioneCubiDM2018
INSERT INTO `tipi_certificato` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (16, 'Prove su cubi D.M. 2018', NULL, 'CertificatoCubi2018.prn', 'Cubetti2018.prn', 'CompressioneCubiDM2018', 'Compressione su cubi', NULL, NULL, 'Lunghezza(mm)', 150, 'Larghezza(mm)', 150, 'Altezza(mm)', 150, 6, 28, 12, 0, 'Verbali.prn', 1);

-- configurazione servizi certificato CompressioneCubiDM2018
update servizi_listino set certificato4 = 16, prove4 = 1 where categoria = 548 and (certificato = 12 or certificato2 = 12 or certificato3 = 12 or certificato4 = 12)

-- associazione tipi materiali al certificato CompressioneCubiDM2018
update tipi_materiale set TipoCertificato2 = 16 where TipoCertificato = 12
update tipi_materiale set TipoCertificato3 = 16 where TipoCertificato2 = 12
update tipi_materiale set TipoCertificato4 = 16 where TipoCertificato3 = 12

-- campo serie.Sigla 16 caratteri
ALTER TABLE serie MODIFY Sigla VARCHAR(16);

-- aggiunta campo serie.Sigla2
alter table serie add column Sigla2 varchar(16) DEFAULT '';


-- nuovo certificato BarreB450 DM2018
INSERT INTO `tipi_certificato` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (17, 'Prove su barre da c.a. B450 D.M. 2018', NULL, 'CertificatoBarreB450_2018.prn', 'AcciaioCAB450_2018.prn', 'TrazionePiegamentoBarreB450_2018', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 11, 0, 'Verbali.prn', 1);

update servizi_listino set certificato2 = 17, prove2 = 1 where categoria = 551 and ID in ('DA01', 'DA02', 'DA03', 'DA04', 'DA05', 'DA09', 'DA10')

update tipi_materiale set TipoCertificato4 = 17 where (TipoCertificato = 11 or TipoCertificato2 = 11 or TipoCertificato3 = 11)

-- aggiunta campo tipi_certificato.Attivo
alter table tipi_certificato add column Attivo INT DEFAULT 1;
update tipi_certificato set Attivo = 0 where Codice in (1, 2, 4, 6, 8, 10);


--------------------------------------------------
-- VERSIONE 4.6.1
--------------------------------------------------

-- correzione ID certificato Cubi da 16 a 18
select * from tipi_materiale where TipoCertificato = 16
select * from tipi_materiale where TipoCertificato2 = 16
select * from tipi_materiale where TipoCertificato3 = 16
select * from tipi_materiale where TipoCertificato4 = 16

update tipi_materiale set TipoCertificato = 18 where TipoCertificato = 16
update tipi_materiale set TipoCertificato2 = 18 where TipoCertificato2 = 16
update tipi_materiale set TipoCertificato3 = 18 where TipoCertificato3 = 16
update tipi_materiale set TipoCertificato4 = 18 where TipoCertificato4 = 16

select * from certificati where TipoCertificato = 16
update certificati set TipoCertificato = 18 where TipoCertificato = 16

select * from servizi_listino where Certificato = 16 Or Certificato2 = 16 or certificato3 = 16 or certificato4 = 16
update servizi_listino set Certificato4 = 18 where Certificato4 = 16

update serie set TipoCertificato = 18 where TipoCertificato = 16

-- nuovo certificato RetiElettrosaldateDM2018   (era 15)
INSERT INTO `tipi_certificato` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (19, 'Prove su reti elettrosaldate D.M. 2018', NULL, 'CertificatoReti2018.prn', 'MinutaReti2018.prn', 'TrazioneRetiDM2018', 'Trazione su reti', 'Distacco sul nodo', NULL, 'Diametro(mm)', NULL, NULL, NULL, NULL, NULL, 6, 0, 15, 0, 'Verbali.prn', 1);

-- configurazione servizi certificato RetiElettrosaldateDM2018
update servizi_listino set certificato3 = 19, prove3 = prove2 where categoria = 551 and certificato2 = 15

-- associazione tipi materiali al certificato RetiElettrosaldateDM2018
update tipi_materiale set TipoCertificato3 = 19 where TipoCertificato2 = 15


-- aggiunta campi servizi_listino.Certificato5, servizi_listino.Prove5 
alter table servizi_listino add column Certificato5 int DEFAULT 0;
alter table servizi_listino add column Prove5 smallint DEFAULT 0;
-- aggiunta campo tipi_materiale.TipoCertificato5 
alter table tipi_materiale add column TipoCertificato5 int DEFAULT 0;


-- nuovo certificato CentroTrasformazioneDM2018   (era 13)
INSERT INTO `tipi_certificato` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`, `Attivo`) 
VALUES (20, 'Prova su barre Centro Trasformazione D.M. 2018', NULL, 'CertificatoBarreCT2018.prn', 'AcciaioCT2018.prn', 'TrazionePiegamentoBarreCTDM2018', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, Lunghezza(cm), NULL, NULL, NULL, 6, 0, 13, 0, 'VerbaleCT.prn', 1);

-- configurazione servizi certificato RetiElettrosaldateDM2018
update servizi_listino set certificato = 3, certificato4 = 13 where categoria  = 551 and ID = 'DA05'

-- associazioni servizi listino a certificato 20
update servizi_listino set certificato5 = 20, prove5 = prove4 where categoria = 551 and certificato4 = 13
select * from servizi_listino where certificato4 = 13 and categoria = 551

-- associazione tipi materiali al certificato RetiElettrosaldateDM2018
update tipi_materiale set TipoCertificato5 = 20 where TipoCertificato3 = 13
select * from tipi_materiale where TipoCertificato = 10