import java.util.Arrays;
import java.util.List;

import ac.il.afeka.Submission.Submission;
import ac.il.afeka.fsm.DFSM;

public class Main implements Submission, Assignment1 {

	public static void main(String[] args) throws Exception {
		Main main = new Main();
		if (main.compute("0 1/a b/0,a,0;0,b,1;1,a,0;1,b,1/0/1", "aaabba")) {
			System.out.print("accept");
		} else {
			System.out.print("Reject");
		}
	}

	@Override
	public List<String> submittingStudentIds() {
		return Arrays.asList("313521965", "4567");
	}

	@Override
	public boolean compute(String dfsmEncoding, String input) throws Exception {
		DFSM d = new DFSM(dfsmEncoding);
		return d.compute(input);
	}

}
