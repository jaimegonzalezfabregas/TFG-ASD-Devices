mkcert -install

rm -rf ../keys/CA
cp -r $(mkcert -CAROOT) ../keys/CA
rm -rf ../../source/server_certs/
mkdir ../../source/server_certs/
cp -r $(mkcert -CAROOT)/rootCA.pem ../../source/server_certs/ca_cert.pem
