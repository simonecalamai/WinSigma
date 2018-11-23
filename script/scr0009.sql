--------------------------------------------------
-- VERSIONE 4.7.5
--------------------------------------------------
-- tabella FATTURE: aggiunta campi
ALTER TABLE `FATTURE`
	ADD COLUMN `IBAN` VARCHAR(27) NULL DEFAULT NULL AFTER `CodiceXML`;

-- tabella AZIENDE: aggiunta campi
ALTER TABLE `AZIENDE`
	ADD COLUMN `IBAN` VARCHAR(27) NULL DEFAULT NULL AFTER `PEC`;
	ADD COLUMN `IBANAppoggio` VARCHAR(27) NULL DEFAULT NULL AFTER `IBAN`;

	
ALTER TABLE `TIPI_PAGAMENTO`
	ADD COLUMN `IBAN` VARCHAR(27) NULL DEFAULT NULL AFTER `CodiceXML`;