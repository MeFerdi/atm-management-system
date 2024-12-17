# ATM Management System

## Usage

```bash
git clone git@git.01.alem.school:skantay/atm-management-system.git
```

```bash
cd atm-management-system
```

```bash
make
```

```bash
./atm
```

## About this Project

The **atm-management-system** is a simulation of a real ATM machine, designed to manage user accounts and transactions. Here's an overview of its features:

- **User Authentication:**
  - Users can log in or register for a new account.

- **Account Management:**
  1. **Create a New Account:**
      - Users can create a new bank account by providing details such as date, desired account ID, country, phone number, initial deposit amount, and account type.
          - Account types include:
            - current (no interest)
            - saving (interest rate: 7%)
            - fixed01 (1-year account, interest rate: 4%)
            - fixed02 (2-year account, interest rate: 5%)
            - fixed03 (3-year account, interest rate: 8%)
      - Users are notified if the entered account ID already exists.

  2. **Update Account Information:**
      - Users can update account information by providing the account ID.
      - Allowed changes include country and phone number.

  3. **Check Account Details:**
      - Users can view details of an existing account by entering the account ID.
      - No information is displayed if the entered account ID does not exist.

  4. **List Owned Accounts:**
      - Users can view a list of all owned bank accounts.

  5. **Make Transactions:**
      - Users can perform transactions such as deposit or withdrawal.
      - Users are prompted to select the account for the transaction, and errors are displayed if the account does not exist or lacks sufficient funds.

  6. **Delete Account:**
      - Users can delete an existing account by providing the account ID.
      - An error message is displayed if the entered account ID does not exist.

  7. **Transfer Ownership:**
      - Users can transfer ownership of their account to another user.
      - Users are prompted for the account ID to transfer and the username of the recipient.

### To [audit](https://01.alem.school/git/root/public/src/commit/b9a78b06d83b099de4832847338508358f478b37/subjects/atm-management-system/audit)

To run the system, use the provided commands: `make` and `./atm`.