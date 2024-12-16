/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package cat.iticbcn.clientiot;

import java.sql.Connection;
import java.sql.SQLException;

/**
 *
 * @author david
 */
public class ClientIoT {

    static final String url = "jdbc:postgresql://192.168.53.2:5432/meso";
    static final String usuario = "daniel";
    static final String contrasena = "daw";

    public static void main(String[] args) {

        DispositiuIot disp = new DispositiuIot();

        try {

            disp.conecta();
            disp.subscriu();

            try (Connection con = ConnectDB.getConnection(url, usuario, contrasena)) {
                System.out.println("Conexion establecida correctamente");

                AccesMethodsToDB access = new AccesMethodsToDB();
                access.selectAlumnes(con);
                access.insertRegistry(con, null);
            } catch (SQLException e) {
                System.out.println("Error de conexión: " + e.getMessage());            
            }

        } catch (Exception e) {
            System.err.println("Error IOT: " + e.getLocalizedMessage());
            System.exit(-1);
        }

    }
}
