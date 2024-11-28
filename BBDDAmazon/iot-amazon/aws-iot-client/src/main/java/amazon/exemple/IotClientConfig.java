package main.java.amazon.exemple;

import com.amazonaws.services.iot.client.AWSIotMqttClient;
import com.amazonaws.services.iot.client.sample.util.SampleUtil;

public class IotClientConfig {
    private AWSIotMqttClient client;

    /**
     * Constructor para configurar el cliente AWS IoT.
     *
     * @param clientEndpoint  Endpoint de AWS IoT (e.g.,
     *                        "<prefix>.iot.<region>.amazonaws.com").
     * @param clientId        Identificador único del cliente.
     * @param certificateFile Ruta al archivo del certificado X.509.
     * @param privateKeyFile  Ruta al archivo de la clave privada.
     */
    public IotClientConfig(String clientEndpoint, String clientId, String certificateFile, String privateKeyFile) {
        KeyStorePasswordPair pair = SampleUtil.getKeyStorePasswordPair(certificateFile, privateKeyFile);
        this.client = new AWSIotMqttClient(clientEndpoint, clientId, pair.keyStore, pair.keyPassword);
    }

    /**
     * Conecta el cliente AWS IoT.
     *
     * @throws Exception Si ocurre algún error durante la conexión.
     */
    public void connect() throws Exception {
        client.connect();
    }

    /**
     * Obtiene el cliente MQTT configurado.
     *
     * @return AWSIotMqttClient configurado.
     */
    public AWSIotMqttClient getClient() {
        return client;
    }
}
