package cat.iticbcn.clientiot;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.amazonaws.services.iot.client.AWSIotMessage;

public class AccesMethodsToDB {

    public void selectAlumnes (Connection con) {
        String sql = "SELECT * FROM registro"; // Consulta SQL
        
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
        
        while (rs.next()) {
            int idRegistro = rs.getInt("id_registro");
            String fecha = rs.getString("fecha");
            String entradaSalida = rs.getString("entrada_salida");
            int idPersona = rs.getInt("id_persona");
            int idEspacio = rs.getInt("id_espacio");

            System.out.println("ID Registro: " + idRegistro + ", Fecha: " + fecha + 
                               ", Entrada/Salida: " + entradaSalida + ", ID Persona: " + idPersona + 
                               ", ID Espacio: " + idEspacio);
        }
        
        } catch (SQLException e) {
            System.out.println("Error al ejecutar la consulta: " + e.getMessage());
        }


    }

    public void insertRegistry(Connection con, AWSIotMessage message) {

        //agafar el message.getStringPayload()
        //fer l'insert a la taula de registres

    }
    
}
