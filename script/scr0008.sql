--------------------------------------------------
-- VERSIONE 4.7.1
--------------------------------------------------
	-- tabella FATTURE: aggiunta campi
ALTER TABLE `FATTURE`
	ADD COLUMN `CodiceXML` INT(10) NULL DEFAULT NULL AFTER `DataDDT`;
