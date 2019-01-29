/*--------------------------------------------------
-- VERSIONE 4.7.14
-------------------------------------------------- 
-- Tabella CONDIZIONI_PAGAMENTO */ 
CREATE TABLE IF NOT EXISTS `CONDIZIONI_PAGAMENTO` (
  `Codice` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Descrizione` varchar(100) DEFAULT '0',
  `CodiceXML` varchar(4) DEFAULT '0',
  PRIMARY KEY (`Codice`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;


INSERT INTO `CONDIZIONI_PAGAMENTO` (`Codice`, `Descrizione`, `CodiceXML`) VALUES
	(1, 'Rate', 'TP01'),
	(2, 'Completo', 'TP02'),
	(3, 'Anticipo', 'TP03');

/* -- Tabella FATTURE */
ALTER TABLE `FATTURE`
ADD COLUMN `CondizioniPagamento` INT(10) NULL DEFAULT NULL AFTER `IBANAppoggio`;
