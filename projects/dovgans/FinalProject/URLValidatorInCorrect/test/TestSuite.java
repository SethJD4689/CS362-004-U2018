import org.junit.runners.Suite;
import org.junit.runner.RunWith;

@RunWith(Suite.class)
@Suite.SuiteClasses({
        ManualTest.class,
        SchemeTest.class,
        FileSchemeTest.class,
        AuthorityTest.class,
        PortTest.class,
        PathTest.class,
        QueryTest.class,
        IsValidTest.class,
        URLTest.class
})

public class TestSuite {

}
