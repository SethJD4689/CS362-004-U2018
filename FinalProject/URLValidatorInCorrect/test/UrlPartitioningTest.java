import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

public class UrlPartitioningTest {

    private final boolean PRINT_TRUE = true;
    private final boolean PRINT_FALSE = true;

    private UrlValidator validator;
    private URL url;

    /**
     *
     */
    @Before
    public void setUp() {

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_ALL_SCHEMES);

        url = new URL();

        // TODO Add variables prior to testing in this section
    }

    /**
     *
     */
    @After
    public void tearDown() {

        // TODO Nothing to put in here at the moment...consider deleting later
    }

    /**
     *
     */
    @Test
    public void testAll(){

    }
}
