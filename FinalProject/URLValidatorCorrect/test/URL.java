/**
 * Basic URL partitioning class used to build URL test cases.
 * Author: Seth Dovgan
 * Version: 01 AUG 18
 */
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

    /**
     * Default Constructor. Sets all value to default.
     */
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

    /**
     * Constructor. Sets the URL partition values and their respective validity.
     * @param scheme - Scheme used to build the URL
     * @param authority - authority used to build the URL
     * @param port - port used to build the URL
     * @param path - path used to build the URL
     * @param query - query used to build the URL
     * @param schemeIsValid - validity of the URL scheme
     * @param authorityIsValid - validity of the URL authority
     * @param portIsValid - validity of the URL port
     * @param pathIsValid - validity of the URL path
     * @param queryIsValid - validity of the URL query
     */
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

    public String getScheme() {

        return scheme;
    }

    public boolean getSchemeIsValid(){

        return schemeIsValid;
    }

    public void setScheme(String scheme, boolean isValid) {

        this.scheme = scheme;
        this.schemeIsValid = isValid;
    }

    public String getAuthority() {

        return authority;
    }

    public boolean getAuthorityIsVAlid() {

        return authorityIsValid;
    }

    public void setAuthority(String authority, boolean isValid) {

        this.authority = authority;
        authorityIsValid = isValid;
    }

    public String getPort() {

        return port;
    }

    public boolean getPortIsValid() {

        return portIsValid;
    }

    public void setPortIsValid(boolean isValid){
        this.portIsValid = isValid;
    }

    public void setPort(String port, boolean isValid) {

        this.port = port;
        portIsValid = isValid;
    }

    public String getPath() {

        return path;
    }

    public boolean getPathIsValid() {

        return pathIsValid;
    }

    public void setPath(String path, boolean isValid) {

        this.path = path;
        pathIsValid = isValid;
    }

    public String getQuery() {

        return query;
    }

    public boolean getQueryIsValid() {

        return queryIsValid;
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
