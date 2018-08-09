
public class URLPart {

    private String part;
    private boolean isValid;

    public URLPart(String part, boolean isValid) {
        this.part = part;
        this.isValid = isValid;
    }

    public String getPart() {
        return part;
    }

    public boolean isValid() {
        return isValid;
    }
}
