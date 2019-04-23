class temp {
    /*
    public boolean compute(String input) throws Exception {
        NDFSM NDFSMtoConvert = new NDFSM(input);
        DFSM convertedNDFSM = NDFSMtoConvert.toDFSM();
        System.out.println("NDFSM to convert:");
        NDFSMtoConvert.prettyPrint(System.out);
        System.out.println("New DFSM from NDFSM:");
        convertedNDFSM.prettyPrint(System.out);
        return true;
    }

    public State createStatesFromSet(Set<State> states) {
        StringBuilder sb = new StringBuilder(State.encodeStateSet(states).replaceAll(" ", ""));
        if (sb.length() > 1 && sb.charAt(0) == '0') {
            sb.replace(0, 1, sb.charAt(1) + "");
            sb.replace(1, 2, "0");
        }
        return new IdentifiedState(Integer.parseInt(sb.toString()));
    }

    public String fixNewStateID(String id) {
        StringBuilder sb = new StringBuilder(id);
        if (id.length() > 1 && id.charAt(0) == '0') {
            sb.replace(0, 1, id.charAt(1) + "");
            sb.replace(1, 2, "0");
        }
        return sb.toString();
    }

    public Set<State> getEClosure(State state) {
        TransitionRelation tr = new TransitionRelation(this.transitions.transitions());
        ArrayList<State> visitedArray = new ArrayList<State>();
        int initialVisitedLength = 1;
        int i = 0;
        visitedArray.add(state);
        while (true) {
            Set<State> atEpsilon = tr.at(visitedArray.get(i), Alphabet.EPSILON);
            for (State s : atEpsilon) {
                if (!visitedArray.contains(s)) {
                    visitedArray.add(s);
                }
            }
            if (initialVisitedLength == visitedArray.size()) {
                break;
            }
            initialVisitedLength = visitedArray.size();
            i++;
        }
        return new HashSet<State>(visitedArray);
    }

    public DFSM toDFSM() {
        TransitionRelation tr = new TransitionRelation(this.transitions.transitions());
        Set<Set<State>> statesByEpsilon = new HashSet<Set<State>>();
        for (State s : this.states) {
            statesByEpsilon.add(getEClosure(s));
        }
        String stateIDinString = fixNewStateID(State.encodeStateSet(getEClosure(initialState)).replaceAll(" ", ""));
        State sTag = new IdentifiedState(Integer.parseInt(stateIDinString));
        ArrayList<State> activeStates = new ArrayList<State>();
        // Compute DeltaTag:
        activeStates.add(sTag);
        Set<Transition> deltaTag = new HashSet<Transition>();
        for (int i = 0; i < activeStates.size(); i++) {
            boolean hasComputed = false;
            for (Transition transition : deltaTag) {
                if (activeStates.get(i).equals(transition.fromState())) {
                    hasComputed = true;
                    break;
                }
            }
            if (!hasComputed) {
                for (char c : this.alphabet) {
                    State newState = null;
                    Set<State> newStatesStates = new HashSet<>();
                    for (State oldState : this.states) {
                        if (activeStates.get(i).encode().contains(oldState.encode())) {
                            newStatesStates.add(oldState);
                        }
                    }
                    for (State q : newStatesStates) {
                        Set<State> transitionsFromq = tr.at(q, c);
                        for (State p : transitionsFromq) {
                            Set<State> temp = getEClosure(p);
                            temp.add(q);
                            newState = createStatesFromSet(temp);
                        }
                        if (newState != null) {
                            Transition newTransition = new Transition(activeStates.get(i), c, newState);
                            boolean transitionExists = false;
                            for (Transition dTag : deltaTag) {
                                if (dTag.fromState() == newTransition.fromState() && dTag.symbol() == newTransition.symbol()) {
                                    transitionExists = true;
                                }
                            }
                            if (!transitionExists) {
                                deltaTag.add(newTransition);
                            }
                        }
                        if (!activeStates.contains(newState)) {
                            activeStates.add(newState);
                        }
                    }
                }
            }
        }
        Set<State> kTag = new HashSet<State>(activeStates);
        Set<State> aTag = new HashSet<State>();
        for (State qTag : activeStates) {
            for (State acceptingState : acceptingStates) {
                if (qTag.encode().contains(acceptingState.encode())) {
                    aTag.add(qTag);
                }
            }
        }
        DFSM convertedNDFSM = null;
        try {
            convertedNDFSM = new DFSM(new HashSet<State>(activeStates), this.alphabet, deltaTag, sTag, aTag);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return convertedNDFSM;
    }
    */
}