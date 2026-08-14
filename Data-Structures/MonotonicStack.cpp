int n; cin >> n;
int a[n];
int nxtgreater[n + 5]{}, prevgreater[n + 5]{};
stack<int> st;
for (int i = n; i>=1; --i) {
    while (!st.empty() && a[i] >= a[st.top()])
        st.pop();
    nxtgreater[i] = (st.empty()? n + 1 : st.top());
    st.push(i);
}

while (!st.empty())
    st.pop();
for (int i = 1; i<=n; ++i) {
    while (!st.empty() && a[i] >= a[st.top()])
        st.pop();
    prevgreater[i] = (st.empty()? 0 : st.top());
    st.push(i);
}
