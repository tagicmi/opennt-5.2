inline DWORD WPAValidateCertCheckFlags(DWORD dwFlags)
{
	if (dwFlags & CERT_STORE_SIGNATURE_FLAG)
		return NTE_BAD_SIGNATURE;
	if (dwFlags & CERT_STORE_TIME_VALIDITY_FLAG)
		return CERT_E_EXPIRED;
	if (dwFlags & CERT_STORE_REVOCATION_FLAG && !(dwFlags & CERT_STORE_NO_CRL_FLAG))
		return CERT_E_REVOKED;
	return ERROR_SUCCESS;
}

inline DWORD WPAValidateCertChain(HCERTSTORE hCertStore, PCCERT_CONTEXT pCertContext, const BYTE* lpRootCert, DWORD cbRootCert) {
	const CERT_CONTEXT* Issuer = NULL;
	DWORD dwFlags = 0;
	DWORD err = 0;
	const CERT_CONTEXT* CurContext = NULL;
	const CERT_CONTEXT* RootContext = NULL;

	RootContext = CertCreateCertificateContext(X509_ASN_ENCODING, lpRootCert, cbRootCert);
	if (RootContext == NULL) {
		err = GetLastError();
		goto done;
	}
	CurContext = CertDuplicateCertificateContext(pCertContext);
	if (CurContext == NULL) {
		err = SEC_E_CERT_UNKNOWN;
		goto done;
	}
	for (;;) {
		dwFlags = CERT_STORE_SIGNATURE_FLAG;
		Issuer = CertGetIssuerCertificateFromStore(hCertStore, CurContext, NULL, &dwFlags);
		if (Issuer != NULL) {
			err = WPAValidateCertCheckFlags(dwFlags);
			if (err != ERROR_SUCCESS) {
				goto done;
			}
			CertFreeCertificateContext(CurContext);
			CurContext = Issuer;
			continue;
		}
		if (Issuer == NULL) {
			dwFlags = CERT_STORE_SIGNATURE_FLAG;
			if (!CertVerifySubjectCertificateContext(CurContext, RootContext, &dwFlags)) {
				err = GetLastError();
				goto done;
			}
			err = WPAValidateCertCheckFlags(dwFlags);
			break;
		}
	}
done:
	if (CurContext != NULL) {
		CertFreeCertificateContext(CurContext);
	}
	if (Issuer != NULL) {
		CertFreeCertificateContext(Issuer);
	}
	if (RootContext != NULL) {
		CertFreeCertificateContext(RootContext);
	}
	return err;
}
