
public class Cliente {
	
	private String id;
	private String password;
	private double donado;
	
	
	Cliente(String id , String password){
		this.id = id;
		this.password = password;
	}
	
	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getPassword() {
		return password;
	}

	public double getDonado() {
		return donado;
	}

	public void setDonado(double donado) {
		this.donado = donado;
	}
	
	public void addDonacion(double donado) {
		this.donado+=donado;
	}
	
	
	
}
