import java.util.Arrays;
import java.util.List;

import ac.il.afeka.Submission.Submission;
import ac.il.afeka.fsm.DFSM;
import ac.il.afeka.fsm.NDFSM;

public class Main implements Submission, Assignment3 {

	public static void main(String[] args) throws Exception {
		Main main = new Main();
		DFSM dfsm = main.convert(		"1 2 3 4 5 6/a b/1,,2;1,a,3;1,b,4;2,a,5;2,a,3;2,b,4;3,a,3;3,b,4;3,b,6;4,,1;5,a,5;5,a,2;5,b,6;6,a,5/1/3 6");
		System.out.println("DFSM:");
		dfsm.prettyPrint(System.out);
	}

	@Override
	public List<String> submittingStudentIds() {
		return Arrays.asList("313521965", "4567");
	}

	@Override
	public DFSM convert(String aNDFSMencoding) throws Exception {
		NDFSM ndfsm = new NDFSM(aNDFSMencoding);
		System.out.println("NDFSM:");
		ndfsm.prettyPrint(System.out);
		System.out.println("--------------------");
		return ndfsm.toDFSM();
	}
}
