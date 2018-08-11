import org.junit.runners.Suite;
import org.junit.runner.RunWith;

@RunWith(Suite.class)
@Suite.SuiteClasses({
        ManualTest.class,
        PartitionsTest.class,
        SchemeTest.class,
        FileSchemeTest.class,
        AuthorityTest.class,
        PortTest.class,
        PathTest.class,
        QueryTest.class,
        IsValidTest.class,
        ProgrammingTest.class
})

public class TestSuite {

}
