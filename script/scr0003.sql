alter table tipi_certificato add LayoutStampaHeader varchar(80);
update tipi_certificato set LayoutStampaHeader = 'CertificatoCubiHdr.prn' where Codice = 1;
update tipi_certificato set LayoutStampaHeader = 'CertificatoCaroteHdr.prn' where Codice = 2;
update tipi_certificato set LayoutStampaHeader = 'CertificatoBarreHdr.prn' where Codice = 3;
update tipi_certificato set LayoutStampaHeader = 'CertificatoTrazioneProfilatiHdr.prn' where Codice = 4;
update tipi_certificato set LayoutStampaHeader = 'CertificatoResilienzaProfilatiHdr.prn' where Codice = 5;
update tipi_certificato set LayoutStampaHeader = 'CertificatoRetiHdr.prn' where Codice = 6;
update tipi_certificato set LayoutStampaHeader = 'CertificatoTrefoliHdr.prn' where Codice = 7;
update tipi_certificato set LayoutStampaHeader = 'CertificatoCubi2003Hdr.prn' where Codice = 8;
update tipi_certificato set LayoutStampaHeader = 'CertificatoCarote2003Hdr.prn' where Codice = 9;
update tipi_certificato set LayoutStampaHeader = 'CertificatoBarreB450Hdr.prn' where Codice = 10;
update tipi_certificato set LayoutStampaHeader = 'CertificatoBarreB450_2010Hdr.prn' where Codice = 11;
update tipi_certificato set LayoutStampaHeader = 'CertificatoCubi2010Hdr.prn' where Codice = 12;
update tipi_certificato set LayoutStampaHeader = 'CertificatoBarreCTHdr.prn' where Codice = 13;
update tipi_certificato set LayoutStampaHeader = 'CertificatoTrazioneProfilati2011Hdr.prn' where Codice = 14;
update tipi_certificato set LayoutStampaHeader = 'CertificatoReti2011Hdr.prn' where Codice = 15;
