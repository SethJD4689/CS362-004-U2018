
public class URL {

    private String scheme;
    private String authority;
    private String port;
    private String path;
    private String query;

    private boolean schemeIsValid;
    private boolean authorityIsValid;
    private boolean portIsValid;
    private boolean pathIsValid;
    private boolean queryIsValid;

    public URL(){

        this.scheme = "";
        this.authority = "";
        this.port = "";
        this.path = "";
        this.query = "";

        this.schemeIsValid = false;
        this.authorityIsValid = false;
        this.portIsValid = true;
        this.pathIsValid = true;
        this.queryIsValid = true;
    }

    public URL(String scheme, String authority, String port, String path,
               String query, boolean schemeIsValid,
               boolean authorityIsValid, boolean portIsValid, boolean pathIsValid,
               boolean queryIsValid) {

        // Partitions
        this.scheme = scheme;
        this.authority = authority;
        this.port = port;
        this.path = path;
        this.query = query;

        // Partitions validity
        this.schemeIsValid = schemeIsValid;
        this.authorityIsValid = authorityIsValid;
        this.portIsValid = portIsValid;
        this.pathIsValid = pathIsValid;
        this.queryIsValid = queryIsValid;
    }

    public void setScheme(String scheme, boolean isValid) {

        this.scheme = scheme;
        this.schemeIsValid = isValid;
    }

    public void setAuthority(String authority, boolean isValid) {

        this.authority = authority;
        authorityIsValid = isValid;
    }

    public void setPort(String port, boolean isValid) {

        this.port = port;
        portIsValid = isValid;
    }

    public void setPath(String path, boolean isValid) {

        this.path = path;
        pathIsValid = isValid;
    }

    public void setQuery(String query, boolean isValid) {

        this.query = query;
        queryIsValid = isValid;
    }

    public String getURL(){

        return scheme + authority + port + path + query;
    }

    public boolean isURLValid(){

        return schemeIsValid && authorityIsValid && portIsValid && pathIsValid
                && queryIsValid;
    }
}
