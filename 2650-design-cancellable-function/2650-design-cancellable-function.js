var cancellable = function(generator) {
    let cancelled = false;
    let finished = false;

    let resolvePromise;
    let rejectPromise;

    const promise = new Promise((resolve, reject) => {
        resolvePromise = resolve;
        rejectPromise = reject;
    });

    const cancel = () => {
        if (finished) return;
        cancelled = true;
    };

    const run = (method, value) => {
        if (finished) return;

        let result;

        try {
            result = generator[method](value);
        } catch (err) {
            finished = true;
            rejectPromise(err);
            return;
        }

        if (result.done) {
            finished = true;
            resolvePromise(result.value);
            return;
        }

        Promise.resolve(result.value).then(
            value => {
                if (finished) return;

                if (cancelled) {
                    cancelled = false;
                    run("throw", "Cancelled");
                } else {
                    run("next", value);
                }
            },
            error => {
                if (finished) return;

                if (cancelled) {
                    cancelled = false;
                    run("throw", "Cancelled");
                } else {
                    run("throw", error);
                }
            }
        );
    };

    run("next");

    return [cancel, promise];
};