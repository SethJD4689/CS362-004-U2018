
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

    public void setPart(String part) {
        this.part = part;
    }

    public boolean isValid() {
        return isValid;
    }

    public void setValid(boolean valid) {
        isValid = valid;
    }
}
