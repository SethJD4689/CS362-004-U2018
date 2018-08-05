import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

public class UrlProgrammingTest {

    private final boolean PRINT_TRUE = true;
    private final boolean PRINT_FALSE = true;

    private UrlValidator validator;
    private URL url;

    @Before
    public void setUp() {

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_ALL_SCHEMES);

        url = new URL();
    }

    @After
    public void tearDown() {
        // TODO Nothing to put in here at the moment...consider deleting later
    }

    @Test
    public void testAll(){

        assertFalse("Hello", validator.isValid("google.com"));
    }

    // Scheme,  Domain Name or IP Address, port, path, query
    // Scheme must end with ":"
    // Scheme must begin with a letter
    // Scheme must only include letters, numbers, "+", ".", and "-"
    // Scheme must not be null
    // Scheme has no length limits
    // Port Range - 0 to 65535
    // Port must be preceded by ":"
    // Domain Name / IP Address Range - 0.0.0.0 to 255.255.255.255
    // Domain Name must start with "//"
    // Domain Name Range - 0 to 63 characters per label
    // Domain Name Range - 127 labels total, separated by periods
    // Domain Name Range - 253 characters total including labels and periods
    // Domain Name Characters - letters (non-case sensitive), numbers and "-"
    // Domain Name must not start or end with a "-"
    // Domain Name must not be all numeric
    // Domain must not be null
    // Path may be empty
    // Path must be preceded by "/"
    // Query must be preceded with a ?
}

