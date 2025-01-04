# Jest Setup and Configuration Guide for Adhoc Ride Management System

This README outlines the steps to set up Jest for testing the Adhoc Ride Management System project, as well as common issues encountered and their solutions.

## Prerequisites

Before proceeding, ensure the following tools are installed on your system:

- **Node.js** (v14 or later)
- **npm** (comes with Node.js)
- **MongoDB** (either local or cloud instance like MongoDB Atlas)

## Project Setup

1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd sanikpod-email-parser
   ```

2. **Install Dependencies**:
   Install the project dependencies specified in the `package.json` file.
   ```bash
   npm install
   ```

3. **Set Up Environment Variables**:
   Create a `.env` file in the root directory with the following content:
   ```env
   MONGO_URI=<your-mongo-db-uri>
   PORT=7500
   ```

   Replace `<your-mongo-db-uri>` with your MongoDB connection string.

4. **Start the Project**:
   Run the project to ensure everything is configured correctly.
   ```bash
   npm run dev
   ```

## Installing and Configuring Jest

1. **Install Jest**:
   Add Jest as a development dependency.
   ```bash
   npm install --save-dev jest
   ```

2. **Install Additional Libraries**:
   For mocking and assertions, install the following:
   ```bash
   npm install --save-dev supertest
   npm install --save-dev @babel/preset-env
   npm install --save-dev @babel/preset-react
   npm install --save-dev jest-environment-node
   ```

3. **Configure Babel**:
   Create a `babel.config.js` file in the root directory with the following content:
   ```javascript
   module.exports = {
     presets: ["@babel/preset-env"],
   };
   ```

4. **Update `package.json` for Jest**:
   Add the following script in `package.json`:
   ```json
   "scripts": {
     "test": "jest"
   }
   ```

5. **Configure Jest**:
   Create a `jest.config.js` file in the root directory:
   ```javascript
   module.exports = {
     testEnvironment: "node",
     moduleFileExtensions: ["js", "jsx"],
   };
   ```

## Writing Tests

- Test files should be placed in a `__tests__` directory or named with `.test.js` or `.spec.js` extensions.
- Example test structure:

  ```plaintext
  backend/
  ├── __tests__/
      ├── routes/
          └── email.routes.test.js
      └── config/
          └── db.test.js
  ```

## Running Tests

Run tests using the following command:
```bash
npm test
```

## Common Issues and Fixes

1. **EADDRINUSE Error (Port Already in Use)**:
   - **Problem**: You may encounter the error: `listen EADDRINUSE: address already in use`.
   - **Solution**: Identify the process using the port and terminate it.
     ```bash
     netstat -ano | findstr :7500
     taskkill /PID <process-id> /F
     ```

2. **process.exit(1) Error During Tests**:
   - **Problem**: Tests may fail if `process.exit` is called in the code.
   - **Solution**: Mock `process.exit` in your tests to avoid termination.
     ```javascript
     jest.spyOn(process, "exit").mockImplementation(() => {});
     ```

3. **Environment Variable Not Found**:
   - **Problem**: The `MONGO_URI` variable is not set.
   - **Solution**: Ensure `.env` is properly configured, and Jest loads it. Use the `dotenv` library if needed.
     ```javascript
     import dotenv from "dotenv";
     dotenv.config();
     ```

4. **MongoDB Mocking Issues**:
   - **Problem**: Mongoose-related tests fail due to real database connections.
   - **Solution**: Mock Mongoose in tests:
     ```javascript
     jest.mock("mongoose", () => ({
       connect: jest.fn(),
     }));
     ```

## Example Test Case: MongoDB Connection

```javascript
import mongoose from "mongoose";
import { connectDB } from "../../config/db.js";

jest.mock("mongoose"); // Mock mongoose

describe("MongoDB Connection", () => {
  it("should connect to MongoDB successfully", async () => {
    mongoose.connect.mockResolvedValueOnce({
      connection: { host: "localhost" },
    });

    console.log = jest.fn(); // Mock console.log

    await connectDB(); // Test connectDB function

    expect(mongoose.connect).toHaveBeenCalledTimes(1);
    expect(mongoose.connect).toHaveBeenCalledWith(process.env.MONGO_URI);
    expect(console.log).toHaveBeenCalledWith("MongoDB Connected: localhost");
  });

  it("should handle connection errors", async () => {
    mongoose.connect.mockRejectedValueOnce(new Error("Connection failed"));

    console.log = jest.fn(); // Mock console.log
    jest.spyOn(process, "exit").mockImplementation(() => {});

    await connectDB(); // Test connectDB function

    expect(mongoose.connect).toHaveBeenCalledTimes(1);
    expect(console.log).toHaveBeenCalledWith("Error: Connection failed");
    expect(process.exit).toHaveBeenCalledWith(1);
  });
});
```

## Conclusion

This guide provides a comprehensive setup for Jest in the Adhoc Ride Management System project. Following these steps will help streamline testing and ensure project maintainability. For further assistance, consult the Jest [documentation](https://jestjs.io/docs/getting-started).

