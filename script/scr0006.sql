-- nuovo certificato CompressioneCubiDM2018
INSERT INTO `tipi_certificato` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`) 
VALUES (16, 'Prove su cubi D.M. 2018', NULL, 'CertificatoCubi2018.prn', 'Cubetti2018.prn', 'CompressioneCubiDM2018', 'Compressione su cubi', NULL, NULL, 'Lunghezza(mm)', 150, 'Larghezza(mm)', 150, 'Altezza(mm)', 150, 6, 28, 12, 0, 'Verbali.prn');

-- configurazione servizi certificato CompressioneCubiDM2018
update servizi_listino set certificato4 = 16, prove4 = 1 where categoria = 548 and (certificato = 12 or certificato2 = 12 or certificato3 = 12 or certificato4 = 12)

-- associazione tipi materiali al certificato CompressioneCubiDM2018
update tipi_materiale set TipoCertificato2 = 16 where TipoCertificato = 12
update tipi_materiale set TipoCertificato3 = 16 where TipoCertificato2 = 12
update tipi_materiale set TipoCertificato4 = 16 where TipoCertificato3 = 12

-- campo serie.Sigla 16 caratteri
ALTER TABLE serie MODIFY Sigla VARCHAR(16);

-- aggiunta campo.Sigla2
alter table serie add column Sigla2 varchar(16) DEFAULT '';
